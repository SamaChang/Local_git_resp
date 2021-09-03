#ifndef KISS_FTR_H
#define KISS_FTR_H

#include "kiss_fft_fix.h"
#ifdef __cplusplus
extern "C" {
#endif

	typedef struct kiss_fftr_state* kiss_fftr_cfg;


	kiss_fftr_cfg fix_kiss_fftr_alloc(int nfft, int inverse_fft, void* mem, size_t* lenmem);
	/*
	nfft must be even

	If you don't care to allocate space, use mem = lenmem = NULL
	*/


	void fix_kiss_fftr(kiss_fftr_cfg cfg, const kiss_fft_scalar* timedata, kiss_fft_cpx* freqdata);
	/*
	input timedata has nfft scalar points
	output freqdata has nfft/2+1 complex points
	*/

	void fix_kiss_fftr2(kiss_fftr_cfg st, const kiss_fft_scalar* timedata, kiss_fft_scalar* freqdata);

	void fix_kiss_fftri(kiss_fftr_cfg cfg, const kiss_fft_cpx* freqdata, kiss_fft_scalar* timedata);

	void fix_kiss_fftri2(kiss_fftr_cfg st, const kiss_fft_scalar* freqdata, kiss_fft_scalar* timedata);

	/*
	input freqdata has  nfft/2+1 complex points
	output timedata has nfft scalar points
	*/

#define kiss_fftr_free speex_free

#ifdef __cplusplus
}
#endif
#endif
