#include "rec/base/RealTime.h"
#include "rec/base/SampleCount.h"

namespace rec {

RealTime::RealTime(const SamplePosition& pos) : time_(pos / 44100.0) {}

}  // namespace rec
