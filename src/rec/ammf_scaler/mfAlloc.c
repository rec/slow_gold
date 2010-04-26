#ifndef _WIN32_WCE
#include <stdio.h>
#endif
#include <stdlib.h>
#include "mfMacros.h"
#ifdef WIN32
#include <windows.h>
#endif
// #ifdef _WIN32_WCE
#include <string.h>
// #endif

/* #define DEBUG_EFENCE */
/* #define DEBUG_ALLOC */
/* #define DEBUG_NO_FREE */

#ifdef DEBUG_ALLOC

#define MAXALLOC 10000

char* AllocationAddresses[MAXALLOC];
long  AllocationSizes[MAXALLOC];
int   AllocationInitialized = 0;

static void InitAlloc()
{
    long i;

    for (i=0; i<MAXALLOC; i++)
    {
	AllocationAddresses[i] = 0;
	AllocationSizes[i] = 0;
    }
    AllocationInitialized = 1;
}

static void StoreAlloc(void* p, long size)
{
    long i;

    if (!AllocationInitialized)
	InitAlloc();

    if (!p)
	abort();	/* out of memory */

    /* test for overlapping allocation */
    for (i=0; i<MAXALLOC; i++)
    {
	if (!AllocationAddresses[i])
	    continue;

	if ((((char*) p) >= AllocationAddresses[i])
	  && (((char*) p) < (AllocationAddresses[i] + AllocationSizes[i])))
	{
	    abort();
	}
    }

    /* add allocation information to first empty spot */
    for (i=0; i<MAXALLOC; i++)
    {
	if (AllocationAddresses[i] == 0)
	{
	    AllocationAddresses[i] = p;
	    AllocationSizes[i] = size;
	    return;
	}
    }

    /* Allocation arrays are not big enough */
    abort();
}

static void RemoveAlloc(void* p)
{
    long i;

    if (!AllocationInitialized)
	InitAlloc();

    for (i=0; i<MAXALLOC; i++)
    {
	if (!AllocationAddresses[i])
	    continue;

	if (AllocationAddresses[i] == p)
	{
	    AllocationAddresses[i] = 0;
	    AllocationSizes[i] = 0;
	    return;
	}
    }

    /* bad free */
    abort();
}

int MfLeakCheck()
{
    long i;
    long nLeaks = 0;
    
    if (!AllocationInitialized)
	return nLeaks;

    for (i=0; i<MAXALLOC; i++)
    {
	if (!AllocationAddresses[i])
	    continue;
	else if (AllocationAddresses[i] != 0)
	    nLeaks++;
    }
    
    return nLeaks;
}
#endif 

#ifdef WIN32
#ifndef _WIN32_WCE
#define SHOW_HEAP_ADDRESS( name, heap )\
{\
    char buffer[256];\
    sprintf(buffer, "** " #name " Heap Address = %x\r\n", heap );\
    OutputDebugString( buffer );\
}
#endif /* not _WIN32_WCE */
static HANDLE MFHeapHandle = 0;
static HANDLE MFHeapCreate()
{
    if (MFHeapHandle == 0)
    {
	MFHeapHandle = HeapCreate(0, 0, 0);
//#ifndef _WIN32_WCE
//	SHOW_HEAP_ADDRESS(MuscleFish, MFHeapHandle);
//#endif
    }
    if (MFHeapHandle == 0)
	return 0;
    return MFHeapHandle;
}
#endif

void* MfMalloc(size_t size)
{
    void* p = 0;
#ifdef DEBUG_EFENCE
    p = (void*) EF_malloc(size);
#else
#if defined(WIN32) && !defined(NORM_ALLOC)
    if (MFHeapCreate() == 0)
	return 0;
    p = HeapAlloc( MFHeapHandle, 0, size );
#else
    p = (void*) malloc(size);
#endif
#endif
#ifdef DEBUG_ALLOC
    StoreAlloc(p, size);
#endif
    return p;
}

void* MfCalloc(size_t nElems, size_t sizeElem)
{
    void* p = 0;
#ifdef DEBUG_EFENCE
    p = (void*) EF_calloc(nElems, sizeElem);
#else
#if defined(_WIN32_WCE)
    p = (void*) malloc(nElems * sizeElem);
    memset(p, 0, (nElems * sizeElem));
#else
#if defined(WIN32) && !defined(NORM_ALLOC) && !defined(_WIN32_WCE)
    if (MFHeapCreate() == 0)
	return 0;
    p = HeapAlloc( MFHeapHandle, HEAP_ZERO_MEMORY, nElems*sizeElem );
#else
    p = (void*) calloc(nElems, sizeElem);
#endif
#endif
#endif
#ifdef DEBUG_ALLOC
    StoreAlloc(p, nElems*sizeElem);
#endif
    return p;
}

void *MfRealloc(void *ptr, size_t size)
{
    void* p = 0;
#ifdef DEBUG_ALLOC
    RemoveAlloc(ptr);
#endif
#ifdef DEBUG_EFENCE
    p = (void*) EF_realloc(ptr, size);
#else
#if defined(WIN32) && !defined(NORM_ALLOC)
    if (MFHeapCreate() == 0)
	return 0;
    p = HeapReAlloc( MFHeapHandle, 0, ptr, size );
#else
    p = (void*) realloc(ptr, size);
#endif
#endif
#ifdef DEBUG_ALLOC
    StoreAlloc(p, size);
#endif
    return p;
}

void MfFree(void* p)
{
#ifndef DEBUG_NO_FREE
    if (p != 0)
    {
#ifdef DEBUG_EFENCE
        EF_free(p);
#else
#if defined(WIN32) && !defined(NORM_ALLOC)
	if (MFHeapHandle)
	    HeapFree( MFHeapHandle, 0, p );
#else
        free(p);
#endif
#endif
#ifdef DEBUG_ALLOC
	RemoveAlloc(p);
#endif
    }
#endif
}

char* MfStrdup(const char* s)
{
    char* newstr = 0;
    if (s)
    {
	newstr = (char*) Malloc(strlen(s)+1);
	if (newstr)
	    strcpy(newstr, s);
    }
    return newstr;
}

