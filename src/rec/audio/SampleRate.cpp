#include "rec/audio/SampleRate.h"

namespace rec {
namespace audio {

namespace {

struct SamplesPerSecond {
  CriticalSection lock_;
  int sampleRate_;
  Broadcaster<int> sampleRateBroadcaster_;
};

inline SamplesPerSecond* getSPS() {
  static SamplesPerSecond sps;
  return &sps;
}

}  // namespace

int getSampleRate() {
  Lock l(getSPS()->lock_);
  return getSPS()->sampleRate_;
}

void setSampleRate(int st) {
  {
    Lock l(getSPS()->lock_);
    LOG(INFO) << "Setting sample rate to " << st;
    getSPS()->sampleRate_ = st;
  }
  getSampleRateBroadcaster()->broadcast(st);
}

Broadcaster<int>* getSampleRateBroadcaster() {
  return &getSPS()->sampleRateBroadcaster_;
}

}  // namespace audio
}  // namespace rec
