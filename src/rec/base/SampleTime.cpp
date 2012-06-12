#include "rec/base/SampleTime.h"

namespace rec {

namespace {

struct SamplesPerSecond {
  CriticalSection lock_;
  SampleTime samplesPerSecond_;
};

inline SamplesPerSecond* getSPS() {
  static SamplesPerSecond sps;
  return &sps;
}

template <typename Type>
static int64 toSampleCount(Type t) {
  return static_cast<int64>(SampleTime::getSamplesPerSecond() * t);
}

}  // namespace

SampleTime SampleTime::getSamplesPerSecond() {
  Lock l(getSPS()->lock_);
  return getSPS()->samplesPerSecond_;
}

void SampleTime::setSamplesPerSecond(SampleTime st) {
  Lock l(getSPS()->lock_);
  getSPS()->samplesPerSecond_ = st;
}

SampleTime::SampleTime(RealTime time) : position_(toSampleCount(time)) {}

}  // namespace rec
