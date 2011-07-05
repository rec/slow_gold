#ifndef __REC_DATA_BINARY__
#define __REC_DATA_BINARY__

#include "rec/base/base.h"

namespace rec {
namespace data {

template <typename Type>
Type* create(const char* data, int len);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_BINARY__
