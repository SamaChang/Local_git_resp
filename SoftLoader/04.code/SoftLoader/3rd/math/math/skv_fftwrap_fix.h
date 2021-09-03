/* Copyright (C) 2005 Jean-Marc Valin
File: fftwrap.h

Wrapper for various FFTs
*/

#ifndef SKV_FFTWRAP_FIX_H
#define SKV_FFTWRAP_FIX_H

#include "../basic/skv_types.h"
#include "../basic/skv_config.h"

#ifdef __cplusplus 
extern "C"
{
#endif

	/** Compute tables for an FFT */
	void* skv_fft_fix_init(int size);
	/** Destroy tables for an FFT */
	void skv_fft_fix_destroy(void* table);

	void skv_fft_fix(void* table, spx_int32_t* in, spx_int32_t* out);

	void skv_ifft_fix(void* table, spx_int32_t* in, spx_int32_t* out);


#ifdef __cplusplus 
}
#endif  

#endif
