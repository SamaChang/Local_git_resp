/* 
File: skv_preprocess.c
*/

#include "skv_preprocess.h"
#include "../basic/skv_config.h"
#include "../basic/skv_types.h"
#include "../basic/os_support.h"
#include "../basic/skv_ulity.h"

#include "../math/skv_math_core.h"
#include "../math/skv_fastmath.h"
#include "../math/skv_math.h"
#include "../math/skv_fftwrap.h"



#ifdef DO_Dereverberation
	#include "skv_wrls_dereverb.h"
#endif
#define SAMPLE_SCALE 8192.0 // MUST be 

/** SKV pre-processor state. */
struct SKVPreprocessState_
{
	/* Basic info */
	int    frame_size;        /**< Number of samples processed each time */
	int    nfft;			  /**< Number of points in the power spectrum */
	int    sampling_rate;     /**< Sampling rate of the input/output */
	int    bits_persample;	  /**< Bits persample of the input/output */
	int	   num_src_channel;	  /**< Number of channels in the input audio data */
	int	   num_use_channel;
	int	   N3;
	int    N4;
	int    N;

	void         * fft_lookup;  /**< Lookup table for the FFT */
	spx_word16_t *  window;     /**< Analysis/Synthesis window */

	int	    in_short_size;
	short * in_short;
	short * in;
	short * out;

	spx_word16_t ** frame;      /**< Processing frame (channel * 2 * ps_size) */
	spx_word16_t * outbuf;      /**< Output buffer (for overlap and add) */
	spx_word16_t * out_frame;   /**< Processing frame (2 * ps_size ) */

	ComplexMatrix  ft;          /**< Processing frame in freq domain (channel * 2 * ps_size) */
	ComplexMatrix  out_ft;      /**< Processing frame in freq domain (channel * 2 * ps_size) */
	spx_word16_t * tft;         /**< Processing frame in freq domain (2*ps_size) */

	int fft_delay_frame;
	int mask_size;
	SKVComplexBuffer* st_fft_buffer;

};

typedef struct SKVPreprocessState_ SKVPreprocessState;
static SKVPreprocessState *st = NULL;

static inline void sin_window(spx_word16_t * w, int wlen)
{
	int i = 0;
	float step = M_PI / float(wlen);
	float v = 0.5 * M_PI / float(wlen);
	for (i = 0; i < wlen; i++)
	{
		w[i] = SKV_SIN(v);
		v = v + step;
	}
}

static inline void preprocess_analysis(SKVPreprocessState * st, short * x, int ch)
{
	if (ch >= st->num_use_channel || st == NULL || x == NULL)
	{
		return;
	}

	int i = 0;
	/* 'Build' input frame */
	for (i = 0; i < st->frame_size; i++)
	{
		//st->frame[ch][st->N3 + i] = x[i] / SAMPLE_SCALE;
		st->frame[ch][st->N3 + i] = x[i] * SAMPLE_SCALE;
	}
	/* Windowing */
	for (i = 0; i < st->N; i++)
	{
		st->frame[ch][i] = st->frame[ch][i] * st->window[i];
	}
	/* Perform FFT */
	skv_fft(st->fft_lookup, st->frame[ch], st->tft);
	st->ft.data[ch * st->ft.c_size + 0].real = st->tft[0];
	st->ft.data[ch * st->ft.c_size + 0].image = st->tft[st->N - 1];
	for (i = 1; i < st->nfft; i++)
	{
		st->ft.data[ch * st->ft.c_size + i].real = st->tft[2 * i - 1];
		st->ft.data[ch * st->ft.c_size + i].image = st->tft[2 * i];
	}
	for (i = 0; i < st->N3; i++)
	{
		//st->frame[ch][i] = x[st->N4 + i] / SAMPLE_SCALE;
		st->frame[ch][i] = x[st->N4 + i] * SAMPLE_SCALE;
	}
}

static inline void preprocess_ianalysis(SKVPreprocessState *st, Complex * fft, spx_word16_t * out)
{
	int i;
	for (i = 0; i < st->nfft; i++)
	{
		//fft[i] = Multi3(fft[i], SAMPLE_SCALE);
		fft[i] = Div3(fft[i], SAMPLE_SCALE);
	}

	st->tft[0] = fft[0].real;
	st->tft[st->N - 1] = fft[0].image;
	for (i = 1; i < st->nfft; i++)
	{
		st->tft[2 * i - 1] = fft[i].real;
		st->tft[2 * i] = fft[i].image;
	}
	skv_ifft(st->fft_lookup, st->tft, out);
}

EXPORT int skv_preprocess_state_init(int sampling_rate, int bits_persample, int num_src_channel)
{
#ifdef  SKV_USE_FASTMATH
	skv_logtab_init();
#endif

	/* Check the recording configure of the input audio data */
	/*
	if ( sampling_rate != 16000 || bits_persample != 16 )
	{
		fprintf(stderr, "Error: %d SampleRate, %d bits_persample, %d num_src_channel cann't be supported", sampling_rate, bits_persample, num_src_channel);
		return INFO_PARAM_ERROR;
	}
	*/
	/* Create the handle of the skv_prepocessing */
	st = (SKVPreprocessState *)speex_alloc(sizeof(SKVPreprocessState));
	if (st == NULL)
	{
		fprintf(stderr, "Error: Unknown error!\n");
		return INFO_UNKNOW_ERROR;
	}

	int i, ch = 0;
	/* Basic Info for multichannel audio*/
	st->num_src_channel   = num_src_channel;
	st->num_use_channel   = num_src_channel;
	st->bits_persample    = bits_persample;
	st->sampling_rate     = sampling_rate;
	
	st->frame_size = FRAME_SIZE;
	st->nfft       = st->frame_size;

	st->N  = 2 * st->nfft;
	st->N3 = st->N - st->frame_size;
	st->N4 = st->frame_size - st->N3;

	st->in_short_size = 0;
	st->in_short	  = NULL;

	/* Create the FFT Table */
	st->fft_lookup = skv_fft_init(st->N);

	/* init the window */
	st->window = (spx_word16_t*)speex_alloc(st->N * sizeof(spx_word16_t));
	sin_window(st->window, st->N);

	/* Create the frame variable for the input multichannel audio */
	st->in  = (short *)speex_alloc(st->frame_size * sizeof(short));
	st->out = (short *)speex_alloc(st->frame_size * sizeof(short));
	st->outbuf = (spx_word16_t*)speex_alloc(st->N3 * sizeof(spx_word16_t));
	st->out_frame = (spx_word16_t*)speex_alloc(st->N * sizeof(spx_word16_t));
	st->frame = (spx_word16_t **)speex_alloc(st->num_use_channel * sizeof(spx_word16_t *));
	for (ch = 0; ch < st->num_use_channel; ch++)
	{
		st->frame[ch] = (spx_word16_t *)speex_alloc(st->N * sizeof(spx_word16_t));
		SPEEX_MEMSET(st->frame[ch], 0.0f, st->N);
	}
	SPEEX_MEMSET(st->outbuf, 0.0f, st->N3);
	SPEEX_MEMSET(st->out_frame, 0.0f, st->N);
	SPEEX_MEMSET(st->in, 0, st->frame_size);
	SPEEX_MEMSET(st->out, 0, st->frame_size);

	/* Create the FFT variable */
	st->ft     = NewComplexMatrix(st->num_use_channel, st->nfft);
	st->out_ft = NewComplexMatrix(1, st->nfft);
	st->tft    = (spx_word16_t *)speex_alloc(st->N * sizeof(spx_word16_t));
	SPEEX_MEMSET(st->tft, 0.0f, st->N);
	
	/* Create the skv_mask_engine handle */
	

	/* Create the mask for mask */
	
	
	/* Create the fft buffer for aligin the delay */
	//st->fft_delay_frame = 1 + skv_mask_engine_get_delay_frame(st->st_mask);

	
	return INFO_RIGHT;
}

EXPORT void skv_preprocess_state_destroy()
{
	if (st == NULL)
	{
		return;
	}
	int ch = 0;
	if (st->fft_lookup != NULL)
	{
		skv_fft_destroy(st->fft_lookup); st->fft_lookup = NULL;
	}
	if (st->in_short != NULL)
	{
		speex_free(st->in_short); st->in_short = NULL;
	}
	if (st->in != NULL)
	{
		speex_free(st->in); st->in = NULL;
	}
	if (st->out != NULL)
	{
		speex_free(st->out); st->out = NULL;
	}
	if (st->window != NULL)
	{
		speex_free(st->window); st->window = NULL;
	}
	if (st->frame != NULL)
	{
		for (ch = 0; ch < st->num_use_channel; ch++)
		{
			if (st->frame[ch] != NULL)
			{
				speex_free(st->frame[ch]); st->frame[ch] = NULL;
			}
		}
		speex_free(st->frame);	st->frame = NULL;
	}
	if (st->outbuf != NULL)
	{
		speex_free(st->outbuf);     st->outbuf = NULL;
	}
	if (st->out_frame != NULL)
	{
		speex_free(st->out_frame);	st->out_frame = NULL;
	}
	st->ft = FreeComplexMatrix(st->ft);
	st->out_ft = FreeComplexMatrix(st->out_ft);
	if (st->tft != NULL)
	{
		speex_free(st->tft); st->tft = NULL;
	}

	if (st->st_fft_buffer != NULL)
	{
		skv_complex_buffer_destroy(st->st_fft_buffer); st->st_fft_buffer = NULL;
	}
	


	speex_free(st); st = NULL;
}

EXPORT int skv_preprocess_short(short* in, short* out, int in_size)
{
	if (st == NULL)
	{
		fprintf(stderr, "You didn't initlize the skv_preprocess!");
		return -1;
	}
	if (in == NULL || in_size < 0)
	{
		fprintf(stderr, "Error: input audio data is null!");
		return -1;
	}
	
	int f = 0;
	int c = 0, i = 0, j = 0;

	int in_samples = in_size / st->num_src_channel;

	int out_s = 0;
	int s = 0;
	int e = s + st->frame_size;
	while (e <= in_samples)
	{
		/* Sumarry the multi-channel into mono-channel and perform FFT */
		for (i = 0; i < st->frame_size; i++)
		{
			int in_data = 0;
			for (c = 0; c < st->num_src_channel; c++)
			{
				in_data += in[(s + i) * st->num_src_channel + c];
			}
			st->in[i] = in_data / st->num_src_channel;
		}
		preprocess_analysis(st, st->in, 0);
		//////huyghuygygyt
		/* Inverse FFT with 1/N scaling and Scale the FFT and Frame */
		preprocess_ianalysis(st, st->ft.data, st->out_frame);

		/* Synthesis window (for WOLA) */
		for (i = 0; i < st->N; i++)
		{
			st->out_frame[i] = st->out_frame[i] * st->window[i];
		}

		/* Perform overlap and add */
		for (i = 0; i < st->N3; i++)
		{
			st->out[i] = st->outbuf[i] + st->out_frame[i];
		}

		for (i = 0; i < st->N4; i++)
		{
			st->out[st->N3 + i] = st->out_frame[st->N3 + i];
		}

		/* Update outbuf */
		for (i = 0; i < st->N3; i++)
		{
			st->outbuf[i] = st->out_frame[st->frame_size + i];
		}

		/* AGC on the out audio */
		/* If out != NULL, Copy the processed data to out*/
		if (out != NULL)
		{
			SPEEX_COPY(out + out_s, st->out, st->frame_size);
			out_s = out_s + st->frame_size;
		}
		else
		{
			for (i = s; i < e; i++)
			{
				for (c = 0; c < st->num_src_channel; c++)
				{
					in[i * st->num_src_channel + c] = st->out[i - s];
				}
			}
		}
		s = e;
		e = s + st->frame_size;
	}
	return s;
}

int skv_preprocess_short_hc(short* in, COMPLEX_OUT* out, int in_size)
{
	if (st == NULL)
	{
		fprintf(stderr, "You didn't initlize the skv_preprocess!");
		return -1;
	}
	if (in == NULL || in_size < 0)
	{
		fprintf(stderr, "Error: input audio data is null!");
		return -1;
	}

	int f = 0;
	int c = 0, i = 0, j = 0;

	int in_samples = in_size / st->num_src_channel;

	int out_s = 0;
	int s = 0;
	int e = s + st->frame_size;
	while (e <= in_samples)
	{
		/* Sumarry the multi-channel into mono-channel and perform FFT */
		for (c = 0; c < st->num_src_channel; c++)
		{
			for (i = 0; i < st->frame_size; i++)
			{
					st->in[i] = in[(s + i) * st->num_src_channel + c];
			}
			preprocess_analysis(st, st->in, c);
		}
		//preprocess_analysis(st, st->in, 0);

		///hc添加，将经过FFT处理后的数据导出
		// If out != NULL, Copy the processed data to out
		if (out != NULL)
		{

			for (int k = 0; k < st->num_use_channel*st->nfft; ++k)
			{
				out[out_s + k].realVal = st->ft.data[k].real;
				out[out_s + k].imagVal = st->ft.data[k].image;
			}
			out_s = out_s + st->frame_size;
		}
		else
		{
			for (i = s; i < e; i++)
			{
				for (c = 0; c < st->num_src_channel; c++)
				{
					in[i * st->num_src_channel + c] = st->out[i - s];
				}
			}
		}

		s = e;
		e = s + st->frame_size;
	}
	return s;
}

EXPORT int skv_preprocess_byte(BYTE* in, short* out, int in_size, int bigOrlittle)
{
	int i;

	if (st == NULL)
	{
		fprintf(stderr, "You didn't initlize the skv_preprocess!");
		return -1;
	}
	if (in == NULL || in_size < 0)
	{
		fprintf(stderr, "Error: input audio data is null!");
		return -1;
	}
	if (bigOrlittle != 0 && bigOrlittle != 1)
	{
		bigOrlittle = skv_bigorsmall();
	}
	int in_short_size = in_size / (st->bits_persample / 8);
	if (st->in_short == NULL)
	{
		st->in_short = (short*)speex_alloc(in_short_size * sizeof(short));
		SPEEX_MEMSET(st->in_short, 0, in_short_size);
		st->in_short_size = in_short_size;
	}
	else if (st->in_short_size != in_short_size)
	{
		st->in_short = (short *)speex_realloc(st->in_short, in_short_size * sizeof(short));
		st->in_short_size = in_short_size;
	}
	st->in_short_size = skv_bytes2shorts(in, st->in_short, in_size, st->bits_persample, bigOrlittle);

	int res = skv_preprocess_short(st->in_short, out, st->in_short_size);
	//res = skv_shorts2bytes(st->in_short, in, res, st->bits_persample, bigOrlittle);
	return res;
}

EXPORT  int skv_preprocess_byte_hc(BYTE * in, COMPLEX_OUT * out, int in_size, int bigOrlittle)
{
	int i;

	if (st == NULL)
	{
		fprintf(stderr, "You didn't initlize the skv_preprocess!");
		return -1;
	}
	if (in == NULL || in_size < 0)
	{
		fprintf(stderr, "Error: input audio data is null!");
		return -1;
	}
	if (bigOrlittle != 0 && bigOrlittle != 1)
	{
		bigOrlittle = skv_bigorsmall();
	}
	int in_short_size = in_size / (st->bits_persample / 8);
	if (st->in_short == NULL)
	{
		st->in_short = (short*)speex_alloc(in_short_size * sizeof(short));
		SPEEX_MEMSET(st->in_short, 0, in_short_size);
		st->in_short_size = in_short_size;
	}
	else if (st->in_short_size != in_short_size)
	{
		st->in_short = (short *)speex_realloc(st->in_short, in_short_size * sizeof(short));
		st->in_short_size = in_short_size;
	}
	st->in_short_size = skv_bytes2shorts(in, st->in_short, in_size, st->bits_persample, bigOrlittle);

	int res = skv_preprocess_short_hc(st->in_short, out, st->in_short_size);
	//res = skv_shorts2bytes(st->in_short, in, res, st->bits_persample, bigOrlittle);
	return res;
}

EXPORT int skv_preprocess_ctl(int request, void* ptr)
{
	if (st == NULL)
	{
		return -1;
	}
	switch (request)
	{
	default:
		speex_warning_int("Unknown skv_preprocess_ctl request: ", request);
		return -1;
	}
	return 0;
}