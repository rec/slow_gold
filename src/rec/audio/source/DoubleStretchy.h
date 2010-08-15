#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHY__

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/stretch/description.pb.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchy : public PositionableAudioSource {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;
  typedef rec::audio::timescaler::Description Description;

  Stretchy(const Description& description, Source* source);

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

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
