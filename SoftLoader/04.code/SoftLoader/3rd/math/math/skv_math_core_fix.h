/************************************************************************************
*				                                                                    *
*	SKV data type	Release 1.0												        *
*	Copyright (c) 2018 by Yonsz Information Technology Co.							*
*	Written by Mr. NieShuai															*
*                                           							            *
*	Function:                                                                       *
*		1) Define some macro definition of data type                                *
*		2) Define basic operations, such as +, -, *, /                              *
*				                                                                    *
*************************************************************************************/

#ifndef SKV_MATH_CORE_FIX_H
#define SKV_MATH_CORE_FIX_H

#define FIXED_POINT

#include "../basic/skv_config.h"
#include "../basic/skv_types.h"

#ifdef __cplusplus 
extern "C"
{
#endif  

#ifndef M_PI
#define M_PI			3.14159265358979323846
#endif

#ifndef M_PI_MUL2
#define M_PI_MUL2		6.28318530717958647692
#endif
#ifndef M_PI_DIV2
#define M_PI_DIV2		1.57079632679489661923
#endif


#define SKV_ABS(x) ((x) < 0 ? (-(x)) : (x))      /**< Absolute integer value. */
#define SKV_ABS16(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define SKV_ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define SKV_MIN(a,b)  ( (a) < (b) ? (a) : (b) )
#define SKV_MAX(a,b)  ( (a) > (b) ? (a) : (b) )
#define SKV_MIN16(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define SKV_MAX16(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define SKV_ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 32-bit value.  */
#define SKV_MIN32(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 32-bit value.   */
#define SKV_MAX32(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 32-bit value.   */

#define ABS(x) ((x) < 0 ? (-(x)) : (x))      /**< Absolute integer value. */
#define ABS16(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define MIN(a,b)  ( (a) < (b) ? (a) : (b) )
#define MAX(a,b)  ( (a) > (b) ? (a) : (b) )
#define MIN16(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define MAX16(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 32-bit value.  */
#define MIN32(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 32-bit value.   */
#define MAX32(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 32-bit value.   */

#ifdef FIXED_POINT

#define Q15ONE 32767

#define LPC_SCALING  8192
#define SIG_SCALING  16384
#define LSP_SCALING  8192.
#define GAMMA_SCALING 32768.
#define GAIN_SCALING 64
#define GAIN_SCALING_1 0.015625

#define LPC_SHIFT    13
#define LSP_SHIFT    13
#define SIG_SHIFT    14
#define GAIN_SHIFT   6

#define VERY_SMALL 0
#define VERY_LARGE32 ((skv_word32_t)2147483647)
#define VERY_LARGE16 ((skv_word16_t)32767)
#define Q15_ONE ((skv_word16_t)32767)

#include "fixed_generic.h"

	/* According to the chip architecture, you can choose the following macro definition for FIXED_POINT*/
#ifdef ARM5E_ASM
#include "fixed_arm5e.h"
#elif defined (ARM4_ASM)
#include "fixed_arm4.h"
#elif defined (BFIN_ASM)
#include "fixed_bfin.h"
#endif

#else


#define Q15ONE 1.0f
#define LPC_SCALING  1.f
#define SIG_SCALING  1.f
#define LSP_SCALING  1.f
#define GAMMA_SCALING 1.f
#define GAIN_SCALING 1.f
#define GAIN_SCALING_1 1.f


#define VERY_SMALL   1e-15f
#define VERY_LARGE32 1e15f
#define VERY_LARGE16 1e15f
#define Q15_ONE ((skv_word16_t)1.f)

#define QCONST16(x,bits) (x)
#define QCONST32(x,bits) (x)

#define NEG16(x) (-(x))
#define NEG32(x) (-(x))
#define EXTRACT16(x) (x)
#define EXTEND32(x) (x)
#define SHR16(a,shift) (a)
#define SHL16(a,shift) (a)
#define SHR32(a,shift) (a)
#define SHL32(a,shift) (a)
#define PSHR16(a,shift) (a)
#define PSHR32(a,shift) (a)
#define VSHR32(a,shift) (a)
#define SATURATE16(x,a) (x)
#define SATURATE32(x,a) (x)
#define SATURATE32PSHR(x,shift,a) (x)

#define PSHR(a,shift)       (a)
#define SHR(a,shift)       (a)
#define SHL(a,shift)       (a)
#define SATURATE(x,a) (x)

#define ADD16(a,b) ((a)+(b))
#define SUB16(a,b) ((a)-(b))
#define ADD32(a,b) ((a)+(b))
#define SUB32(a,b) ((a)-(b))
#define MULT16_16_16(a,b)     ((a)*(b))
#define MULT16_16(a,b)     ((skv_word32_t)(a)*(skv_word32_t)(b))
#define MAC16_16(c,a,b)     ((c)+(skv_word32_t)(a)*(skv_word32_t)(b))

#define MULT16_32_Q11(a,b)     ((a)*(b))
#define MULT16_32_Q13(a,b)     ((a)*(b))
#define MULT16_32_Q14(a,b)     ((a)*(b))
#define MULT16_32_Q15(a,b)     ((a)*(b))
#define MULT16_32_P15(a,b)     ((a)*(b))

#define MAC16_32_Q11(c,a,b)     ((c)+(a)*(b))
#define MAC16_32_Q15(c,a,b)     ((c)+(a)*(b))

#define MAC16_16_Q11(c,a,b)     ((c)+(a)*(b))
#define MAC16_16_Q13(c,a,b)     ((c)+(a)*(b))
#define MAC16_16_P13(c,a,b)     ((c)+(a)*(b))
#define MULT16_16_Q11_32(a,b)     ((a)*(b))
#define MULT16_16_Q13(a,b)     ((a)*(b))
#define MULT16_16_Q14(a,b)     ((a)*(b))
#define MULT16_16_Q15(a,b)     ((a)*(b))
#define MULT16_16_P15(a,b)     ((a)*(b))
#define MULT16_16_P13(a,b)     ((a)*(b))
#define MULT16_16_P14(a,b)     ((a)*(b))

#define DIV32_16(a,b)     (((skv_word32_t)(a))/(skv_word16_t)(b))
#define PDIV32_16(a,b)     (((skv_word32_t)(a))/(skv_word16_t)(b))
#define DIV32(a,b)     (((skv_word32_t)(a))/(skv_word32_t)(b))
#define PDIV32(a,b)     (((skv_word32_t)(a))/(skv_word32_t)(b))

#endif

#ifdef __cplusplus 
}
#endif  

#endif