#ifndef __REC_UTIL_FORMATTIME__
#define __REC_UTIL_FORMATTIME__

#include "rec/base/base.h"

namespace rec {
namespace util {

const String formatTime(double time, bool flash = false,
                        bool displayMs = true,
                        bool displayHours = false);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FORMATTIME__
