#include "rec/base/SampleTime.h"

namespace rec {

namespace {

struct SamplesPerSecond {
  CriticalSection lock_;
  int64 sampleRate_;
};

inline SamplesPerSecond* getSPS() {
  static SamplesPerSecond sps;
  return &sps;
}

}  // namespace

int64 SampleTime::getSampleRate() {
  Lock l(getSPS()->lock_);
  return getSPS()->sampleRate_;
}

void SampleTime::setSampleRate(int64 st) {
  Lock l(getSPS()->lock_);
  LOG(INFO) << "Setting sample rate to " << st;
  getSPS()->sampleRate_ = st;
}

SampleTime::SampleTime(RealTime t)
    : position_(static_cast<int64>(getSampleRate() * t)) {
}

}  // namespace rec
