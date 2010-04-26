#ifndef _MFMALLOC_H
#define _MFMALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

extern void* MfMalloc(size_t size);
extern void* MfCalloc(size_t nElems, size_t elemSize);
extern void* MfRealloc(void *ptr, size_t size);
extern void  MfFree(void* ptr);
extern char* MfStrdup(const char* s);

#ifdef __cplusplus
}
#endif

#endif /* _MFMALLOC_H */
