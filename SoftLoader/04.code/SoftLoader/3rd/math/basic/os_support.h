/* Copyright (C) 2007 Jean-Marc Valin
File: os_support.h
This is the (tiny) OS abstraction layer. Aside from math.h, this is the
only place where system headers are allowed.
*/
#ifndef OS_SUPPORT_H
#define OS_SUPPORT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef OS_SUPPORT_CUSTOM
#include "os_support_custom.h"
#endif

/** Speex wrapper for calloc. To do your own dynamic allocation, all you need to do is replace this function, speex_realloc and speex_free
NOTE: speex_alloc needs to CLEAR THE MEMORY */
#ifndef OVERRIDE_SPEEX_ALLOC
static inline void *speex_alloc(int size)
{
	/* WARNING: this is not equivalent to malloc(). If you want to use malloc()
	or your own allocator, YOU NEED TO CLEAR THE MEMORY ALLOCATED. Otherwise
	you will experience strange bugs */
	return calloc(size, 1);
}
#endif

/** Same as speex_alloc, except that the area is only needed inside a Speex call (might cause problem with wideband though) */
#ifndef OVERRIDE_SPEEX_ALLOC_SCRATCH
static inline void *speex_alloc_scratch(int size)
{
	/* Scratch space doesn't need to be cleared */
	return calloc(size, 1);
}
#endif

/** Speex wrapper for realloc. To do your own dynamic allocation, all you need to do is replace this function, speex_alloc and speex_free */
#ifndef OVERRIDE_SPEEX_REALLOC
static inline void *speex_realloc(void *ptr, int size)
{
	return realloc(ptr, size);
}
#endif

/** Speex wrapper for calloc. To do your own dynamic allocation, all you need to do is replace this function, speex_realloc and speex_alloc */
#ifndef OVERRIDE_SPEEX_FREE
static inline void speex_free(void *ptr)
{
	free(ptr);
}
#endif

/** Same as speex_free, except that the area is only needed inside a Speex call (might cause problem with wideband though) */
#ifndef OVERRIDE_SPEEX_FREE_SCRATCH
static inline void speex_free_scratch(void *ptr)
{
	free(ptr);
}
#endif

/** Copy n elements from src to dst. The 0* term provides compile-time type checking  */
#ifndef OVERRIDE_SPEEX_COPY
#define SPEEX_COPY(dst, src, n) (memcpy((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** Copy n elements from src to dst, allowing overlapping regions. The 0* term
provides compile-time type checking */
#ifndef OVERRIDE_SPEEX_MOVE
#define SPEEX_MOVE(dst, src, n) (memmove((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** For n elements worth of memory, set every byte to the value of c, starting at address dst */
#ifndef OVERRIDE_SPEEX_MEMSET
#define SPEEX_MEMSET(dst, c, n) (memset((dst), (c), (n)*sizeof(*(dst))))
#endif


#ifndef OVERRIDE_SPEEX_FATAL
static inline void _speex_fatal(const char *str, const char *file, int line)
{
	fprintf(stderr, "Fatal (internal) error in %s, line %d: %s\n", file, line, str);
	exit(1);
}
#endif

#ifndef OVERRIDE_SPEEX_WARNING
static inline void speex_warning(const char *str)
{
#ifndef DISABLE_WARNINGS
	fprintf(stderr, "warning: %s\n", str);
#endif
}
#endif

#ifndef OVERRIDE_SPEEX_WARNING_INT
static inline void speex_warning_int(const char *str, int val)
{
#ifndef DISABLE_WARNINGS
	fprintf(stderr, "warning: %s %d\n", str, val);
#endif
}
#endif

#ifndef OVERRIDE_SPEEX_NOTIFY
static inline void speex_notify(const char *str)
{
#ifndef DISABLE_NOTIFICATIONS
	fprintf(stderr, "notification: %s\n", str);
#endif
}
#endif

#ifndef OVERRIDE_SPEEX_PUTC
/** Speex wrapper for putc */
static inline void _speex_putc(int ch, void *file)
{
	FILE *f = (FILE *)file;
	fprintf(f, "%c", ch);
}
#endif

#define speex_fatal(str) _speex_fatal(str, __FILE__, __LINE__);
#define speex_assert(cond) {if (!(cond)) {speex_fatal("assertion failed: " #cond);}}

#ifndef RELEASE
static inline void print_vec(float *vec, int len, char *name)
{
	int i;
	printf("%s ", name);
	for (i = 0; i<len; i++)
		printf(" %f", vec[i]);
	printf("\n");
}
#endif

#endif

