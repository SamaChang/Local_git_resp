/* Copyright (C) 2005 Jean-Marc Valin
File: fftwrap.h

Wrapper for various FFTs
*/

#ifndef SKV_FFTWRAP_H
#define SKV_FFTWRAP_H

#include "../basic/skv_types.h"
#include "../basic/skv_config.h"

#ifdef __cplusplus 
extern "C"
{
#endif

/** Compute tables for an FFT */
void *skv_fft_init(int size);

/** Destroy tables for an FFT */
void skv_fft_destroy(void *table);
#ifdef  FIXED_POINT
	void skv_fft(void *table, spx_int32_t *in, spx_int32_t *out);
	void skv_ifft(void *table, spx_int32_t *in, spx_int32_t *out);	
#endif 
#ifndef FIXED_POINT
	/** Forward (real to half-complex) transform */
	void skv_fft(void *table, spx_word16_t *in, spx_word16_t *out);
	/** Backward (half-complex to real) transform */
	void skv_ifft(void *table, spx_word16_t *in, spx_word16_t *out);
#endif 


/** Forward (real to half-complex) transform of float data */
void skv_fft_float(void *table, float *in, float *out);

/** Backward (half-complex to real) transform of float data */
void skv_ifft_float(void *table, float *in, float *out);

/** Forward (real to ComplexMatrix) transform of float data */
void skv_fft_complexmat(void *table, float *in, ComplexMatrix out);

/** Backward (ComplexMatrix to real) transform of float data */
void skv_ifft_complexmat(void *table, ComplexMatrix in, float *out);

#ifdef __cplusplus 
}
#endif  

#endif
