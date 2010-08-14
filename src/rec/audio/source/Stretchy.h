#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

#include <vector>

#include "rec/audio/stretch/description.pb.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
class Stretchy : public PositionWrappy<Source> {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;

  Stretchy(const Description& description, Source* source);

  virtual int getTotalLength();
  virtual void setNextReadPosition(int position);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 private:
  int processOneChunk(const AudioSourceChannelInfo& info);
  void getNextAudioBlockFromSource(int numSamples);

  const Description description_;
  Source* const source_;
  const int channels_;
  bool isLooping_;
  AudioSampleBuffer buffer_;
  AudioTimeScaler scaler_;
  std::vector<float*> outOffset_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_STRETCHY_AUDIO_SOURCE
