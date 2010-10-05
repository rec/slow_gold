/*	
 *	MFmacros - Misc utility macros
 *	Copyright (C) 1996 Muscle Fish LLC
 *	All Rights Reserved
 */

#ifndef _MFMACROS_H
#define _MFMACROS_H 

#include <stdlib.h>
#if defined(unix)
#include <sys/param.h>
#include <sys/types.h>
#endif
#ifdef WIN32
#ifndef _WIN32_WCE
#include <sys/types.h>
#endif
#endif
#include "mfAlloc.h"

#ifndef YES_NO
#define YES_NO
#define YES	1
#define NO	0
#endif /* YES_NO */

#define MASK(num, mask)		    (((num) & (mask)) > 0)

#define Malloc  MfMalloc
#define Realloc MfRealloc
#define Calloc  MfCalloc
#define Strdup  MfStrdup
#define Free    MfFree

/* Use Strdup() everywhere now, instead of strdup() or _strdup(). */
/*
#if (defined(macintosh) || defined(WIN32))
#define strdup _strdup
#endif
*/

#ifndef MIN
#define MIN(a,b)		    (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)		    (((a) > (b)) ? (a) : (b))
#endif
#define CONSTRAIN(x, a, b)	    MIN(MAX(x, a), b)
#ifndef ABS
#define ABS(x)			    ((x) >= 0) ? (x) : (-(x))
#endif
#define SIGN(x)			    (((x) >= 0) ? 1 : -1)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_TWOPI
#define M_TWOPI 6.28318530717958647692
#endif

#endif /* _MFMACROS_H */
