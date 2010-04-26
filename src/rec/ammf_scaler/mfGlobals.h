/*
 *----------------------------------------------------------------------------
 * Copyright notice:
 * (c) Copyright 1996 Muscle Fish LLC
 * All rights reserved.
 *
 * This program is protected as an unpublished work under the U.S. copyright
 * laws. The above copyright notice is not intended to effect a publication of
 * this work.
 *
 * This program is the confidential and proprietary information of Muscle
 * Fish.  Neither the binaries nor the source code may be redistributed 
 * without prior written permission from Muscle Fish. 
 *----------------------------------------------------------------------------
 *
 * File: mfGlobals.h
 */

#ifndef _mfGlobals_h
#define _mfGlobals_h

#include <string.h>
#ifdef macintosh
#include <MacTypes.h>
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifdef unix
typedef int	Boolean;
#endif
#if defined(WIN32) || defined(_WIN32_WCE)
typedef int	Boolean;
#endif
typedef char*	MFString;

#ifdef STDCALL
#define MF_CALLCONV __stdcall
#else
#define MF_CALLCONV
#endif

#endif /* _mfGlobals_h */
