/* Copyright (C) 2017 SKV
Written by Shuai Nie */
/**
*  @file skv_preprocess.h
*  @brief SKV preprocessor. The preprocess can do automatic echo cancel(AEC)
*/

#ifndef SKV_ULITY_H
#define SKV_ULITY_H

#include "skv_types.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
	int skv_bigorsmall();
	int skv_bytes2floats(BYTE * in, float * out, int in_size, int bSamples, int bs);
	int skv_floats2bytes(float * in, BYTE * out, int in_size, int bSamples, int bs);
	int skv_bytes2shorts(BYTE * in, short * out, int in_size, int bSamples, int bs);
	int skv_shorts2bytes(short * in, BYTE * out, int in_size, int bSamples, int bs);
	time_t skv_datestr2sec(char* pszDate);
	char * skv_strlwr(char *s);
	void skv_print(char * key, char * str);
	void skv_itoa(int data, char * buffer);

#ifdef __cplusplus
}
#endif

/** @}*/
#endif
