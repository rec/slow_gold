#ifndef __REC_AUDIO_SOURCE_BUFFERED_H__
#define __REC_AUDIO_SOURCE_BUFFERED_H__

#include "juce_amalgamated.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

class Buffered : public PositionableAudioSource {
 public:
  Buffered(int numChannels, int numSamples)
      : buffer_(numChannels, numSamples), looping_(true) {
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& destInfo) {
    int length = getTotalLength();

    AudioSampleBuffer* dest = destInfo.buffer;
    int destStart = destInfo.startSample;
    int numSamples = destInfo.numSamples;

    for (int copied = 0; copied < numSamples; ) {
      int blockSize = jmin(numSamples - copied, position_.remaining());
      copy(blockSize, position_.position_, buffer_, destStart + copied, dest);
      position_.increment(blockSize);
    }
  }

  virtual void setNextReadPosition(int p) { position_ = p; }
  virtual int getNextReadPosition() const { return position_; }
  virtual int getTotalLength() const { return buffer_.getNumSamples(); }

  virtual void prepareToPlay(int samples, double rate) {}
  virtual void releaseResources() {}
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping(bool looping) { looping_ = looping; }

  AudioSampleBuffer* buffer() { return buffer_; }

 private:
  AudioSampleBuffer buffer_;
  Circular position_;

  // Are we looping?
  bool looping_;

  DISALLOW_COPY_AND_ASSIGN(Buffered);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERED_H__
