#ifndef __REC_UTIL_FORMATTIME__
#define __REC_UTIL_FORMATTIME__

#include "rec/base/base.h"

namespace rec {
namespace util {

const String formatTime(RealTime time, bool flash = false,
                        bool displayHours = false,
                        bool leadingZeros = true,
                        int decimals = 3);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FORMATTIME__
