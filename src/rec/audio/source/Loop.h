#ifndef __REC_LOOP_AUDIO_SOURCE
#define __REC_LOOP_AUDIO_SOURCE

#include "juce_amalgamated.h"
#include "rec/base/base.h"
#include "rec/util/Math.h"
#include "rec/audio/CopySamples.h"

namespace rec {
namespace audio {
namespace source {

class Loop : public PositionableAudioSource {
 public:
  Loop(const AudioSampleBuffer& source, int position = 0)
      : source_(source),
        position_(position) {
    jassert(source.getNumSamples() > position);
  }

  ~Loop() {}

  virtual void setNextReadPosition(int p) { position_ = p; }
  virtual int getNextReadPosition() const { return position_; }
  virtual int getTotalLength() const { return source_.getNumSamples(); }
  virtual bool isLooping() const { return true; }

  virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}
  virtual void releaseResources() {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    int copied = 0;
    int length = getTotalLength();
    while (copied < info.numSamples) {
      int samplesToCopy = std::min(length - position_, info.numSamples - copied);
      copySamples(samplesToCopy, position_, source_, info.startSample + copied, info.buffer);
      copied += samplesToCopy;
      position_ = (position_ + samplesToCopy) % length;
    }
  }

 private:
  const AudioSampleBuffer& source_;
  int position_;

  DISALLOW_COPY_AND_ASSIGN(Loop);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_LOOP_AUDIO_SOURCE
