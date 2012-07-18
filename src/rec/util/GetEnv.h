#ifndef __REC_UTIL_GETENV__
#define __REC_UTIL_GETENV__

#include "rec/base/base.h"

namespace rec {
namespace util {

String getEnv(const char* name, const String& dflt);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_GETENV__
