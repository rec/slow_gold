#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/stretch/description.pb.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace source {

class Stretchy : public PositionWrappy {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;
  typedef rec::audio::timescaler::Description Description;

  Stretchy(const Description& description, PositionableAudioSource* source);

  virtual int getTotalLength();
  virtual void setNextReadPosition(int position);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 private:
  int processOneChunk(const AudioSourceChannelInfo& info);
  void getNextAudioBlockFromSource(int numSamples);

  const Description description_;
  const int channels_;
  AudioSampleBuffer buffer_;
  AudioTimeScaler scaler_;
  std::vector<float*> outOffset_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
