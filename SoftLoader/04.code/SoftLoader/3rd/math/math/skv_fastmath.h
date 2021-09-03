/************************************************************************************
*				                                                                    *
*	SKV data type	Release 1.0												        *
*	Copyright (c) 2018 by Yonsz Information Technology Co.							*
*	Written by Mr. NieShuai															*
*                                           							            *
*	Function:                                                                       *
*		Some basic math function implement by lookup table                          *
*       Only floating computation                                                   *
*				                                                                    *
*************************************************************************************/

#ifndef _SKV_FASTMATH_H
#define _SKV_FASTMATH_H

#include <math.h>

#include "../basic/skv_config.h"
#include "skv_math_core.h"

#ifdef __cplusplus 
extern "C"
{ 
#endif  

#ifdef  SKV_USE_FASTMATH
	#define SKV_USE_FASTEXP
	#define SKV_USE_FASTLOG
	#define SKV_USE_FASTANGLE
	#define SKV_USE_FASTSQRTF
#endif


typedef float ieee754_float32_t;

void skv_logtab_init(); // You only need to intialize the logtab once. You can call this function in the init function of your moduals

ieee754_float32_t skv_fast_log2(ieee754_float32_t x);


#ifdef SKV_USE_FASTEXP
	#define LITTLE_ENDIAN  1
	static union
	{
		double d;
		struct 
		{
			#ifdef LITTLE_ENDIAN
					int j, i;
			#else 
					int i, j;
			#endif
		} n;
	} _eco;
	#define EXP_A (1048576 / 0.69314718055994530942)
	#define EXP_C 60801
	#define SKV_EXP(y) (_eco.n.i = EXP_A*(y) + (1072693248 - EXP_C), _eco.d)
#else
	#define        SKV_EXP(x)         (expf(x))
#endif 


#ifdef SKV_USE_FASTLOG
	#define        SKV_LOG2_V         (0.69314718055994530942)
	#define        SKV_LOG10_V        (2.30258509299404568402)

	#define        SKV_LOG2(x)        (skv_fast_log2(x))
	#define        SKV_LOG10(x)       (skv_fast_log2(x)*(SKV_LOG2_V/SKV_LOG10_V))//这里有个除以SKV_LOG10_V的操作
	#define        SKV_LOG(x)         (skv_fast_log2(x)*SKV_LOG2_V)//这里只乘以SKV_LOG2_V
#else 
	#define        SKV_LOG2(x)        (log2f(x))
	#define        SKV_LOG10(x)       (log10f(x))
	#define        SKV_LOG(x)         (logf(x))
#endif
 
float skv_fast_sin(float angle);
float skv_fast_cos(float angle);
float skv_fast_atan2(float y, float x);
#ifdef SKV_USE_FASTANGLE
	#define        SKV_SIN(x)         (skv_fast_sin(x))
	#define        SKV_COS(x)         (skv_fast_cos(x))
	#define        SKV_ATAN2(y,x)     (skv_fast_atan2(y,x))
#else 
	#define        SKV_SIN(x)         (sinf(x))
	#define        SKV_COS(x)         (cosf(x))
	#define        SKV_ATAN2(y,x)     (atan2f(x))
#endif

float skv_fast_invsqrtf(float x);
float skv_fast_sqrtf(float x);
#ifdef SKV_USE_FASTSQRTF
	#define        SKV_SQRTF(x)       (skv_fast_sqrtf(x))
	#define        SKV_INVSQRTF(x)    (skv_fast_invsqrtf(x))
#else 
	#define        SKV_SQRTF(x)       (sqrtf(x))
	#define        SKV_INVSQRTF(x)    (1./sqrtf(x))
#endif

#ifdef __cplusplus 
}
#endif  

#endif
