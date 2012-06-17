#ifndef __REC_AUDIO_SAMPLERATE__
#define __REC_AUDIO_SAMPLERATE__

#include "rec/util/Listener.h"

namespace rec {
namespace audio {

struct SampleRate {
  SampleRate() : rate_(0) {}
  SampleRate(int r) : rate_(r) {}
  operator int() const { return rate_; }
  SampleRate& operator=(int r) { rate_ = r; return *this; }
  SampleRate& operator=(SampleRate r) { rate_ = r.rate_; return *this; }

 private:
  int rate_;
};


SampleRate getSampleRate();
void setSampleRate(SampleRate);

Broadcaster<SampleRate>* getSampleRateBroadcaster();


}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SAMPLERATE__
