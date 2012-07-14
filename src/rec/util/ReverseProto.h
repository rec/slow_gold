#ifndef __REC_UTIL_REVERSEPROTO__
#define __REC_UTIL_REVERSEPROTO__

#include <google/protobuf/message.h>

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
void reverseProto(google::protobuf::RepeatedPtrField<Type>* items) {
  for (int i = 0, size = items->size(); i < size / 2; ++i)
    items->SwapElements(i, size - i - 1);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_REVERSEPROTO__
