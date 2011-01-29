#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/audio/stretch/Stretch.h"

namespace rec {
namespace audio {
namespace source {

using stretch::Stretch;

class Stretchy : public Wrappy {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;

  Stretchy(PositionableAudioSource* s,
           const Stretch& desc = Stretch::default_instance());
  ~Stretchy();

  virtual int64 getTotalLength() const;
  virtual void setNextReadPosition(int64 position);
  virtual int64 getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

 private:
  int64 processOneChunk(const juce::AudioSourceChannelInfo& info);

  Stretch description_;
  int channels_;
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
