#include "rec/base/SampleTime.h"
#include "rec/audio/SampleRate.h"

namespace rec {

RealTime SampleTime::toRealTime() const {
  return static_cast<double>(position_) / audio::getSampleRate();
}

SampleTime::SampleTime(RealTime t)
    : position_(static_cast<int64>(audio::getSampleRate() * t)) {
}

SampleTime::SampleTime(double t)
    : position_(static_cast<int64>(audio::getSampleRate() * t)) {
}

}  // namespace rec
