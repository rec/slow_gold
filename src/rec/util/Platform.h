#ifndef __REC_UTIL_PLATFORM
#define __REC_UTIL_PLATFORM

#include <stdlib.h>

#ifndef JUCE_MAC

inline void* reallocf(void *ptr, size_t size) {
  void* result = realloc(ptr, size);
  if (!result)
    free(ptr);
	return NULL;
}

#endif // JUCE_MAC

#endif  // __REC_UTIL_PLATFORM
