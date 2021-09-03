/* Copyright (C) 2005-2006 Jean-Marc Valin
File: fftwrap.c

Wrapper for various FFTs

*/
#include "../basic/skv_config.h"

#include "../basic/skv_types.h"
#include "../basic/os_support.h"
#include "skv_fftwrap.h"

#define MAX_FFT_SIZE 2048

#ifdef FIXED_POINT
static int maximize_range(spx_int32_t *in, spx_int32_t *out, spx_int32_t bound, int len)
{
	int i, shift;
	spx_int32_t max_val = 0;
	for (i = 0; i<len; i++)
	{
		if (in[i]>max_val)
			max_val = in[i];
		if (-in[i]>max_val)
			max_val = -in[i];
	}
	shift = 0;
	while (max_val <= (bound >> 1) && max_val != 0)
	{
		max_val <<= 1;
		shift++;
	}
	for (i = 0; i<len; i++)
	{
		out[i] = SHL16(in[i], shift);
	}
	return shift;
}

static void renorm_range(spx_int32_t *in, spx_int32_t *out, int shift, int len)
{
	int i;
	for (i = 0; i<len; i++)
	{
		out[i] = PSHR16(in[i], shift);
	}
}
#endif

#ifdef USE_SMALLFT

#include "../math/smallft.h"
#include <math.h>

void *skv_fft_init(int size)
{
	struct drft_lookup *table;
	table = (struct drft_lookup *)speex_alloc(sizeof(struct drft_lookup));
	spx_drft_init((struct drft_lookup *)table, size);
	return (void*)table;
}

void skv_fft_destroy(void *table)
{
	spx_drft_clear((struct drft_lookup *)table);
	speex_free(table);
}

void skv_fft(void *table, float *in, float *out)
{
	if (in == out)
	{
		int i;
		float scale = 1. / ((struct drft_lookup *)table)->n;
		speex_warning("FFT should not be done in-place");
		for (i = 0; i<((struct drft_lookup *)table)->n; i++)
			out[i] = scale*in[i];
	}
	else {
		int i;
		float scale = 1. / ((struct drft_lookup *)table)->n;
		for (i = 0; i<((struct drft_lookup *)table)->n; i++)
			out[i] = scale*in[i];
	}
	spx_drft_forward((struct drft_lookup *)table, out);
}

void skv_ifft(void *table, float *in, float *out)
{
	if (in == out)
	{
		speex_warning("FFT should not be done in-place");
	}
	else {
		int i;
		for (i = 0; i<((struct drft_lookup *)table)->n; i++)
			out[i] = in[i];
	}
	spx_drft_backward((struct drft_lookup *)table, out);
}

#elif defined(USE_INTEL_MKL)
#include <mkl.h>

struct mkl_config {
	DFTI_DESCRIPTOR_HANDLE desc;
	int N;
};

void *skv_fft_init(int size)
{
	struct mkl_config *table = (struct mkl_config *) speex_alloc(sizeof(struct mkl_config));
	table->N = size;
	DftiCreateDescriptor(&table->desc, DFTI_SINGLE, DFTI_REAL, 1, size);
	DftiSetValue(table->desc, DFTI_PACKED_FORMAT, DFTI_PACK_FORMAT);
	DftiSetValue(table->desc, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
	DftiSetValue(table->desc, DFTI_FORWARD_SCALE, 1.0f / size);
	DftiCommitDescriptor(table->desc);
	return table;
}

void skv_fft_destroy(void *table)
{
	struct mkl_config *t = (struct mkl_config *) table;
	DftiFreeDescriptor(t->desc);
	speex_free(table);
}

void skv_fft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	struct mkl_config *t = (struct mkl_config *) table;
	DftiComputeForward(t->desc, in, out);
}

void skv_ifft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	struct mkl_config *t = (struct mkl_config *) table;
	DftiComputeBackward(t->desc, in, out);
}

#elif defined(USE_INTEL_IPP)

#include <ipps.h>

struct ipp_fft_config
{
	IppsDFTSpec_R_32f *dftSpec;
	Ipp8u *buffer;
};

void *skv_fft_init(int size)
{
	int bufferSize = 0;
	int hint;
	struct ipp_fft_config *table;

	table = (struct ipp_fft_config *)speex_alloc(sizeof(struct ipp_fft_config));

	/* there appears to be no performance difference between ippAlgHintFast and
	ippAlgHintAccurate when using the with the floating point version
	of the fft. */
	hint = ippAlgHintAccurate;

	ippsDFTInitAlloc_R_32f(&table->dftSpec, size, IPP_FFT_DIV_FWD_BY_N, hint);

	ippsDFTGetBufSize_R_32f(table->dftSpec, &bufferSize);
	table->buffer = ippsMalloc_8u(bufferSize);

	return table;
}

void skv_fft_destroy(void *table)
{
	struct ipp_fft_config *t = (struct ipp_fft_config *)table;
	ippsFree(t->buffer);
	ippsDFTFree_R_32f(t->dftSpec);
	speex_free(t);
}

void skv_fft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	struct ipp_fft_config *t = (struct ipp_fft_config *)table;
	ippsDFTFwd_RToPack_32f(in, out, t->dftSpec, t->buffer);
}

void skv_ifft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	struct ipp_fft_config *t = (struct ipp_fft_config *)table;
	ippsDFTInv_PackToR_32f(in, out, t->dftSpec, t->buffer);
}

#elif defined(USE_GPL_FFTW3)

#include <fftw3.h>

struct fftw_config {
	float *in;
	float *out;
	fftwf_plan fft;
	fftwf_plan ifft;
	int N;
};

void *skv_fft_init(int size)
{
	struct fftw_config *table = (struct fftw_config *) speex_alloc(sizeof(struct fftw_config));
	table->in = fftwf_malloc(sizeof(float) * (size + 2));
	table->out = fftwf_malloc(sizeof(float) * (size + 2));

	table->fft = fftwf_plan_dft_r2c_1d(size, table->in, (fftwf_complex *)table->out, FFTW_PATIENT);
	table->ifft = fftwf_plan_dft_c2r_1d(size, (fftwf_complex *)table->in, table->out, FFTW_PATIENT);

	table->N = size;
	return table;
}

void skv_fft_destroy(void *table)
{
	struct fftw_config *t = (struct fftw_config *) table;
	fftwf_destroy_plan(t->fft);
	fftwf_destroy_plan(t->ifft);
	fftwf_free(t->in);
	fftwf_free(t->out);
	speex_free(table);
}


void skv_fft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	int i;
	struct fftw_config *t = (struct fftw_config *) table;
	const int N = t->N;
	float *iptr = t->in;
	float *optr = t->out;
	const float m = 1.0 / N;
	for (i = 0; i<N; ++i)
		iptr[i] = in[i] * m;

	fftwf_execute(t->fft);

	out[0] = optr[0];
	for (i = 1; i<N; ++i)
		out[i] = optr[i + 1];
}

void skv_ifft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	int i;
	struct fftw_config *t = (struct fftw_config *) table;
	const int N = t->N;
	float *iptr = t->in;
	float *optr = t->out;

	iptr[0] = in[0];
	iptr[1] = 0.0f;
	for (i = 1; i<N; ++i)
		iptr[i + 1] = in[i];
	iptr[N + 1] = 0.0f;

	fftwf_execute(t->ifft);

	for (i = 0; i<N; ++i)
		out[i] = optr[i];
}

#elif defined(USE_KISS_FFT)

#include "../math/kiss_fftr.h"
#include "../math/kiss_fft.h"

struct kiss_config {
	kiss_fftr_cfg forward;
	kiss_fftr_cfg backward;
	int N;
};

void *skv_fft_init(int size)
{
	struct kiss_config *table;
	table = (struct kiss_config*)speex_alloc(sizeof(struct kiss_config));
	table->forward = kiss_fftr_alloc(size, 0, NULL, NULL);
	table->backward = kiss_fftr_alloc(size, 1, NULL, NULL);
	table->N = size;
	return table;
}

void skv_fft_destroy(void *table)
{
	struct kiss_config *t = (struct kiss_config *)table;
	speex_free(t->forward);//kiss_fftr_free
	speex_free(t->backward);//kiss_fftr_free
	speex_free(table);
}

#ifdef FIXED_POINT

void skv_fft(void *table, spx_int32_t *in, spx_int32_t *out)
{
	int shift;
	struct kiss_config *t = (struct kiss_config *)table;
	shift = maximize_range(in, in, 32000, t->N);
	kiss_fftr2(t->forward, in, out);
	renorm_range(in, in, shift, t->N);
	renorm_range(out, out, shift, t->N);
}

#else

void skv_fft(void *table, spx_word16_t *in, spx_word16_t *out)
{
	int i;
	float scale;
	struct kiss_config *t = (struct kiss_config *)table;
	scale = 1. / t->N;
	kiss_fftr2(t->forward, in, out);
	for (i = 0; i<t->N; i++)
		out[i] *= scale;
}
#endif

void skv_ifft(void *table, spx_int32_t *in, spx_int32_t *out)
{
	struct kiss_config *t = (struct kiss_config *)table;
	kiss_fftri2(t->backward, in, out);
}

#else

#error No other FFT implemented

#endif


#ifdef FIXED_POINT
/*#include "smallft.h"*/

void skv_fft_float(void *table, float *in, float *out)
{
	int i;
#ifdef USE_SMALLFT
	int N = ((struct drft_lookup *)table)->n;
#elif defined(USE_KISS_FFT)
	int N = ((struct kiss_config *)table)->N;
#else
#endif
#ifdef VAR_ARRAYS
	spx_word16_t _in[N];
	spx_word16_t _out[N];
#else
	spx_int32_t _in[MAX_FFT_SIZE];
	spx_int32_t _out[MAX_FFT_SIZE];
#endif
	for (i = 0; i<N; i++)
		_in[i] = (int)floor(.5 + in[i]);
	skv_fft(table, _in, _out);
	for (i = 0; i<N; i++)
		out[i] = _out[i];
#if 0
	if (!fixed_point)
	{
		float scale;
		struct drft_lookup t;
		spx_drft_init(&t, ((struct kiss_config *)table)->N);
		scale = 1. / ((struct kiss_config *)table)->N;
		for (i = 0; i<((struct kiss_config *)table)->N; i++)
			out[i] = scale*in[i];
		spx_drft_forward(&t, out);
		spx_drft_clear(&t);
	}
#endif
}

void skv_ifft_float(void *table, float *in, float *out)
{
	int i;
#ifdef USE_SMALLFT
	int N = ((struct drft_lookup *)table)->n;
#elif defined(USE_KISS_FFT)
	int N = ((struct kiss_config *)table)->N;
#else
#endif
#ifdef VAR_ARRAYS
	spx_word16_t _in[N];
	spx_word16_t _out[N];
#else
	spx_int32_t _in[MAX_FFT_SIZE];
	spx_int32_t _out[MAX_FFT_SIZE];
#endif
	for (i = 0; i<N; i++)
		_in[i] = (int)floor(.5 + in[i]);
	skv_ifft(table, _in, _out);
	for (i = 0; i<N; i++)
		out[i] = _out[i];
#if 0
	if (!fixed_point)
	{
		int i;
		struct drft_lookup t;
		spx_drft_init(&t, ((struct kiss_config *)table)->N);
		for (i = 0; i<((struct kiss_config *)table)->N; i++)
			out[i] = in[i];
		spx_drft_backward(&t, out);
		spx_drft_clear(&t);
	}
#endif
}

#else

void skv_fft_float(void *table, float *in, float *out)
{
	skv_fft(table, in, out);
}
void skv_ifft_float(void *table, float *in, float *out)
{
	skv_ifft(table, in, out);
}
void skv_fft_complexmat(void *table, float *in, ComplexMatrix out)
{
	struct drft_lookup * l = (struct drft_lookup *)table;
	spx_word16_t * ft = (spx_word16_t*)out.data;
	skv_fft(table, in, ft);

	spx_word16_t first_imag = ft[l->n - 1];

	SPEEX_MOVE(ft + 2, ft + 1, l->n-2);
	ft[1] = first_imag;
}
void skv_ifft_complexmat(void *table, ComplexMatrix in, float *out)
{
	struct drft_lookup * l = (struct drft_lookup *)table;
	spx_word16_t * ft = (spx_word16_t*)in.data;

	spx_word16_t first_imag = ft[1];
	SPEEX_MOVE(ft + 1, ft + 2, l->n - 2);
	ft[l->n - 1] = first_imag;
	skv_ifft(table, ft, out);
}

#endif
