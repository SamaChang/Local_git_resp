// Microsoft version of 'inline'
#define inline __inline

//#define FIXED_POINT
//#define MIPS_DSP
//#define ARM_NEON_16
//#define ARM_NEON_8

#define OS_LINUX
//#define OS_ANDROID

// In Visual Studio, _M_IX86_FP=1 means /arch:SSE was used, likewise
// _M_IX86_FP=2 means /arch:SSE2 was used.
// Also, enable both _USE_SSE and _USE_SSE2 if we're compiling for x86-64
#if _M_IX86_FP >= 1 || defined(_M_X64)
#define _USE_SSE
#endif

#if _M_IX86_FP >= 2 || defined(_M_X64)
#define _USE_SSE2
#endif

// Visual Studio support alloca(), but it always align variables to 16-bit
// boundary, while SSE need 128-bit alignment. So we disable alloca() when
// SSE is enabled.
#ifndef _USE_SSE
#  define USE_ALLOCA
#endif

/* Default to floating point */
#ifndef FIXED_POINT
#  define FLOATING_POINT
#  define USE_SMALLFT
#else
#  define USE_KISS_FFT
#endif

/* We don't support visibility on Win32 */
#define EXPORT
#define SKV_USE_FASTMATH
//#define SKV_USE_FASTERMATH

//#define DO_Dereverberation     /* Do online WRLS-based Dereverberation */
#define DO_MNR                 /* Do MNR */
//#define DO_SPEEX_AGC			
#define DO_WEBRTC_AGC	

//#define FLOAT_FBANK
#define FIX_FBANK
#define FIXED_GRU

//#define DO_Smooth_Filtering
