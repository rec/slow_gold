#include "Platform.h"

#if _MSC_VER

void * reallocf(void *ptr, size_t size) {
	void* result = realloc(ptr, size);
	if (result == NULL)
		free(ptr);
	return result;
}

#endif //_MSC_VER