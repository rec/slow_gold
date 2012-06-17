#include "rec/audio/SampleRate.h"

namespace rec {
namespace audio {

namespace {

struct SampleRateSingleton {
  SampleRateSingleton() : sampleRate_(44100) {}

  CriticalSection lock_;
  SampleRate sampleRate_;
  Broadcaster<SampleRate> broadcaster_;
};

inline SampleRateSingleton* getSRS() {
  static SampleRateSingleton sps;
  return &sps;
}

}  // namespace

SampleRate getSampleRate() {
  Lock l(getSRS()->lock_);
  return getSRS()->sampleRate_;
}

void setSampleRate(SampleRate st) {
  {
    Lock l(getSRS()->lock_);
    LOG(INFO) << "Setting sample rate to " << st;
    getSRS()->sampleRate_ = st;
  }
  getSampleRateBroadcaster()->broadcast(st);
}

Broadcaster<SampleRate>* getSampleRateBroadcaster() {
  return &getSRS()->broadcaster_;
}

}  // namespace audio
}  // namespace rec
