/* Copyright (C) 2005-2006 Jean-Marc Valin
File: fftwrap.c

Wrapper for various FFTs

*/
#include "../basic/skv_config.h"
#include "../basic/skv_types.h"
#include "../basic/os_support.h"
#include "skv_fftwrap_fix.h"

#define MAX_FFT_SIZE 8192

static int maximize_range(spx_int32_t* in, spx_int32_t* out, spx_int32_t bound, int len)
{
	int i, shift;
	spx_int32_t max_val = 0;
	for (i = 0; i < len; i++)
	{
		if (in[i] > max_val)
			max_val = in[i];
		if (-in[i] > max_val)
			max_val = -in[i];
	}
	shift = 0;
	while (max_val <= (bound >> 1) && max_val != 0)
	{
		max_val <<= 1;
		shift++;
	}
	for (i = 0; i < len; i++)
	{
		out[i] = SHL16(in[i], shift);
	}
	return shift;
}

static void renorm_range(spx_int32_t * in, spx_int32_t * out, int shift, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		out[i] = PSHR16(in[i], shift);
	}
}

#include "kiss_fftr_fix.h"
#include "kiss_fft_fix.h"

struct kiss_config {
	kiss_fftr_cfg forward;
	kiss_fftr_cfg backward;
	int N;
};

void* skv_fft_fix_init(int size)
{
	struct kiss_config* table;
	table = (struct kiss_config*)speex_alloc(sizeof(struct kiss_config));
	table->forward = fix_kiss_fftr_alloc(size, 0, NULL, NULL);
	table->backward = fix_kiss_fftr_alloc(size, 1, NULL, NULL);
	table->N = size;
	return table;
}

void skv_fft_fix_destroy(void* table)
{
	struct kiss_config* t = (struct kiss_config*)table;
	speex_free(t->forward);//kiss_fftr_free
	speex_free(t->backward);//kiss_fftr_free
	speex_free(table);
}

void skv_fft_fix(void* table, spx_int32_t * in, spx_int32_t * out)
{
	int shift;
	struct kiss_config* t = (struct kiss_config*)table;
	shift = maximize_range(in, in, 32000, t->N);
	fix_kiss_fftr2(t->forward, in, out);
	renorm_range(in, in, shift, t->N);
	renorm_range(out, out, shift, t->N);
}

void skv_ifft_fix(void* table, spx_int32_t * in, spx_int32_t * out)
{
	struct kiss_config* t = (struct kiss_config*)table;
	fix_kiss_fftri2(t->backward, in, out);
}