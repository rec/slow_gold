#ifndef __REC_LOOP_AUDIO_SOURCE
#define __REC_LOOP_AUDIO_SOURCE

#include "juce_amalgamated.h"

#include "rec/audio/FillQueue.h"
#include "rec/util/math.h"

namespace rec {
namespace audio {
namespace source {

class Loop : public PositionableAudioSource {
 public:
  Loop(const AudioSampleBuffer& source)
      : source_(source),
        position_(0) {
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
    int channels = std::min(source_.getNumChannels(),
                            info.buffer->getNumChannels());
    while (copied < info.numSamples) {
      int samplesToCopy = std::min(getTotalLength() - position_, info.numSamples - copied);
      for (int c = 0; c < channels; ++c) {
        info.buffer->copyFrom(c, info.startSample + copied,
                              source_, c, position_ % getTotalLength(), samplesToCopy);
      }
      copied += samplesToCopy;
      position_ += samplesToCopy;
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
