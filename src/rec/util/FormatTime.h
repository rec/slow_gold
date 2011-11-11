#ifndef __REC_UTIL_FORMATTIME__
#define __REC_UTIL_FORMATTIME__

#include "rec/base/RealTime.h"

namespace rec {
namespace util {

const String formatTime(RealTime time,
                        RealTime maxTime,
                        bool flash = false,
                        bool leadingZeros = true,
                        int decimals = 3);


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FORMATTIME__
