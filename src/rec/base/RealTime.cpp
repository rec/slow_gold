#include "rec/base/SampleTime.h"

namespace rec {

RealTime::RealTime(const SampleTime& pos) : time_(pos.toRealTime()) {}

}  // namespace rec
