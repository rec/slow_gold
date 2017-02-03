#pragma once

#include <stdlib.h>

#ifndef JUCE_MAC

inline void* reallocf(void *ptr, size_t size) {
  void* result = realloc(ptr, size);
  if (!result)
    free(ptr);
	return nullptr;
}

#endif // JUCE_MAC

