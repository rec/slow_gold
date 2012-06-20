#ifndef __REC_UTIL_FORMATTIME__
#define __REC_UTIL_FORMATTIME__

#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

const String formatTime(SampleTime time,
                        SampleTime mTime,
                        SampleRate rate,
                        bool flash = false,
                        bool leadingZeros = true,
                        int decimals = 3);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FORMATTIME__
