#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/source/TimeScaler.h"
#include "rec/audio/source/Stretchy.pb.h"

namespace rec {
namespace audio {
namespace source {

class Stretchy : public Wrappy {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;
  Stretchy(Source* s,
           const StretchyProto& desc = StretchyProto::default_instance());
  ~Stretchy();

  virtual int getTotalLength() const;
  virtual void setNextReadPosition(int position);
  virtual int getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

 private:
  int processOneChunk(const juce::AudioSourceChannelInfo& info);

  StretchyProto description_;
  int channels_;
  AudioSampleBuffer buffer_;
  AudioTimeScaler scaler_;
  std::vector<float*> outOffset_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

double timeScale(const StretchyProto& d);
double pitchScale(const StretchyProto& d);


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
