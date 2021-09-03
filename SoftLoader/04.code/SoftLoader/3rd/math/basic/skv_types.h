/************************************************************************************
*				                                                                    *
*	SKV data type	Release 1.0												        *
*	Copyright (c) 2018 by Yonsz Information Technology Co.							*
*	Written by Mr. NieShuai															*
*                                           							            *
*	Function:                                                                       *
*		Define basic data type, complex type, matrix type                           *
*				                                                                    *
*************************************************************************************/

#ifndef _SKV_TYPES_H
#define _SKV_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "skv_fixed.h"
#include "skv_config.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

#ifdef MIPS_DSP
	typedef signed char v4i8 __attribute__((vector_size(4)));
	typedef short v2q15 __attribute__((vector_size(4)));
	typedef short v2i16 __attribute__((vector_size(4)));
	typedef int q31;
	typedef int i32;
	typedef long long a64;
	typedef unsigned int ui32;
#endif // MIPS_DSP


/* Basic Data Type */
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned int       DWORD;

typedef signed char skv_int8_t;
typedef unsigned char skv_uint8_t;

typedef signed short skv_int16_t;
typedef unsigned short skv_uint16_t;

typedef signed int skv_int32_t;
typedef unsigned int skv_uint32_t;

typedef signed long long skv_int64_t;
typedef unsigned long long skv_uint64_t;

typedef float skv_word16_t;
typedef double skv_word32_t;

typedef signed char spx_int8_t;
typedef unsigned char spx_uint8_t;

typedef signed short spx_int16_t;
typedef unsigned short spx_uint16_t;

typedef signed int spx_int32_t;
typedef unsigned int spx_uint32_t;

typedef signed long long spx_int64_t;
typedef unsigned long long spx_uint64_t;

typedef float spx_word16_t;
typedef double spx_word32_t;

//#ifdef FIXED_POINT
	typedef int spx_mem_t;
	typedef int spx_coef_t;
	typedef int spx_lsp_t;
	typedef int spx_sig_t;
//#else
//	typedef float spx_mem_t;
//	typedef float spx_coef_t;
//	typedef float spx_lsp_t;
//	typedef float spx_sig_t;
//#endif // 

/* Complex Type */
typedef struct Complex
{
	skv_word16_t real;
	skv_word16_t image;
} Complex;

typedef struct Complex_int8
{
	skv_int8_t real;
	skv_int8_t image;
} Complex_int8;
typedef struct Complex_uint8
{
	skv_uint8_t real;
	skv_uint8_t image;
} Complex_uint8;

typedef struct Complex_short
{
	skv_int16_t real;
	skv_int16_t image;
} Complex_short;
typedef struct Complex_ushort
{
	skv_uint16_t real;
	skv_uint16_t image;
} Complex_ushort;

typedef struct Complex_int
{
	skv_int32_t real;
	skv_int32_t image;
} Complex_int;

typedef struct Complex_uint
{
	skv_uint32_t real;
	skv_uint32_t image;
} Complex_uint;

typedef struct Complex_long
{
	skv_int64_t real;
	skv_int64_t image;
} Complex_long;
typedef struct Complex_ulong
{
	skv_uint64_t real;
	skv_uint64_t image;
} Complex_ulong;

typedef struct Complex_float
{
	skv_word16_t real;
	skv_word16_t image;
} Complex_float;
typedef struct Complex_double
{
	skv_word32_t real;
	skv_word32_t image;
} Complex_double;


/* Complex Matrix Type */
typedef struct ComplexMatrix
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex * data;
} ComplexMatrix;

typedef struct ComplexMatrix_int8
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_int8 * data;
} ComplexMatrix_int8;
typedef struct ComplexMatrix_uint8
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_uint8 * data;
} ComplexMatrix_uint8;

typedef struct ComplexMatrix_short
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_short * data;
} ComplexMatrix_short;
typedef struct ComplexMatrix_ushort
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_ushort * data;
} ComplexMatrix_ushort;

typedef struct ComplexMatrix_int
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_int * data;
} ComplexMatrix_int;
typedef struct ComplexMatrix_uint
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_uint * data;
} ComplexMatrix_uint;

typedef struct ComplexMatrix_long
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_long * data;
} ComplexMatrix_long;
typedef struct ComplexMatrix_ulong
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_ulong * data;
} ComplexMatrix_ulong;

typedef struct ComplexMatrix_float
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_float * data;
} ComplexMatrix_float;
typedef struct ComplexMatrix_double
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	Complex_double * data;
} ComplexMatrix_double;


/* Real Matrix Type */
typedef struct RealMatrix
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_word16_t * data;
} RealMatrix;

typedef struct RealMatrix_int8
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_int8_t * data;
} RealMatrix_int8;
typedef struct RealMatrix_uint8
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_uint8_t * data;
} RealMatrix_uint8;

typedef struct RealMatrix_short
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_int16_t * data;
} RealMatrix_short;
typedef struct RealMatrix_ushort
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_uint16_t * data;
} RealMatrix_ushort;

typedef struct RealMatrix_int
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_int32_t * data;
} RealMatrix_int;
typedef struct RealMatrix_uint
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_uint32_t * data;
} RealMatrix_uint;

typedef struct RealMatrix_long
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_int64_t * data;
} RealMatrix_long;
typedef struct RealMatrix_ulong
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_uint64_t * data;
} RealMatrix_ulong;

typedef struct RealMatrix_float
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_word16_t * data;
} RealMatrix_float;
typedef struct RealMatrix_double
{
	skv_uint32_t r_size;
	skv_uint32_t c_size;
	skv_word32_t * data;
} RealMatrix_double;

#ifdef __cplusplus
}
#endif

#endif  /* _SKV_TYPES_H */
