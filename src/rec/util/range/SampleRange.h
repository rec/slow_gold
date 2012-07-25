#ifndef __REC_UTIL_SAMPLERANGE__
#define __REC_UTIL_SAMPLERANGE__

#include "rec/base/SampleTime.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace util {

typedef Range<SampleTime> SampleRange;
typedef SampleRange::Set SampleRangeSet;
typedef SampleRange::Vector SampleRangeVector;

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_SAMPLERANGE__
