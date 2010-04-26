#ifndef __REC_BUFFER_COPY
#define __REC_BUFFER_COPY

#include <string.,h

#include <algorithm>

namespace rec {
namespace buffer {

// Try to fill up to 'size' entries in 'out', using as many entries from 'in' as
// are needed.  Note that the number of entries consumed from in might more or
// less than 'size'.
template <typename In, typename Out>
Size copy(Size size, In in, Out out);

template <typename Type>
Size copy(Size size, std::pair<Type*, Type*>* in, Type* out) {
  size = std::min(size, in->second - in->first);
  memmove(out, in->begin, size * sizeof(Type));
  in->begin += size;
  return size;
}

}  // namespace buffer
}  // namespace rec

#endif  // __REC_BUFFER_COPY
