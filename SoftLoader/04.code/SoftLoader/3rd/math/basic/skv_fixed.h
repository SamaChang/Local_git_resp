/************************************************************************************
*				                                                                    *
*	SKV_fixed	Release 1.0												            *
*	Copyright (c) 2018 by Yonsz Information Technology Co.							*
*	Written by Mr. NieShuai															*
*                                           							            *
*	Function:                                                                       *
*		Fixed-type operator on macro definition                                     *
*				                                                                    *
*************************************************************************************/

#ifndef _SKV_FIXED_H
#define _SKV_FIXED_H

#ifdef __cplusplus
extern "C" {
#endif

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
#define VERY_LARGE32 ((spx_word32_t)2147483647)
#define VERY_LARGE16 ((spx_word16_t)32767)
//#define Q15_ONE ((spx_word16_t)32767)

#define ABS(x) ((x) < 0 ? (-(x)) : (x))      /**< Absolute integer value. */
#define ABS16(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define MIN16(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define MAX16(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 32-bit value.  */
#define MIN32(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 32-bit value.   */
#define MAX32(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 32-bit value.   */

#ifdef FIXED_DEBUG
#include "fixed_debug.h"
#else

#include "../math/fixed_generic.h"

#ifdef ARM5E_ASM
#include "fixed_arm5e.h"
#elif defined (ARM4_ASM)
#include "fixed_arm4.h"
#elif defined (BFIN_ASM)
#include "fixed_bfin.h"
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif  /* _SKV_FIXED_H */
