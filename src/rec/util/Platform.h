#ifndef __REC_UTIL_PLATFORM
#define __REC_UTIL_PLATFORM

#include <stdlib.h>

#if _MSC_VER
void * reallocf(void *ptr, size_t size);

#endif //_MSC_VER




#endif  // __REC_UTIL_PLATFORM