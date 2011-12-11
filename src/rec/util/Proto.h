#ifndef __REC_UTIL_PROTO__
#define __REC_UTIL_PROTO__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Proto>
string getTypeName() {
  return Proto::default_instance().GetTypeName();
}

// A little slower because it uses reflection.
const string& getTypeName(const Message&);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PROTO__
