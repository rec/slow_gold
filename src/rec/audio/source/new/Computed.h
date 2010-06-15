#ifndef __REC_AUDIO_SOURCE_COMPUTED_H__
#define __REC_AUDIO_SOURCE_COMPUTED_H__

#include "juce_amalgamated.h"
#include "rec/audio/source/new/source/Buffered.h"
#include "rec/buffer/blocks.h"

namespace rec {
namespace audio {
namespace buffer {

inline void mergeInto(const Block& block, BlockList* list) {
  BlockSet::iterator i = list.begin();
  for (; i != list.end() && i->second >= block.first; ++i);

  if (i == list.end()) {
    list.insert(end, block);

  } else {
    BlockSet::iterator begin = i;
    for (++i; i != list.end() && i->first <= block.second; ++i);

    begin->first = jmin(block.first, begin->first);
    begin->second = jmax((i - 1)->second, block.second);
    list.erase(begin + 1, i);
  }
}

template <typename Command>
class Computed {
 public:
  Computed(int length) : length_(length) {}

  void request(const Block& request) {
    ScopedLock l(lock_);
    nextBlock_ = request;
  }

  Block getNextBlock() {
    ScopedLock l(lock_);


    Block b(nextBlock_);
    BlockSet::iterator i = finishedBlocks_.upper_bound(b.second);
    if (i != finishedBlocks_.end()) {

    }
    nextBlock.first = nextBlock.second + 1;
    return b;
  }


 private:
  const int length;
  BlockSet list;
  Block nextBlock_;
  CriticalSection lock_;


  Buffered(const AudioSampleBuffer& buffer)
      : buffer_(buffer), position_(0), looping_(true) {
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& destInfo) {
    int length = getTotalLength();

    AudioSampleBuffer* dest = destInfo.buffer;
    int destStart = destInfo.startSample;
    int numSamples = destInfo.numSamples;

    for (int copied = 0; copied < numSamples; ) {
      int blockSize = jmin(numSamples - copied, length - position_);
      copy(blockSize, position_, buffer_, destStart + copied, dest);
      position_ = (position_ + blockSize) % length;
    }
  }

  virtual void setNextReadPosition(int p) { position_ = p; }
  virtual int getNextReadPosition() const { return position_; }
  virtual int getTotalLength() const { return buffer_.getNumSamples(); }

  virtual void prepareToPlay(int samples, double rate) {}
  virtual void releaseResources() {}
  virtual bool isLooping() const { return looping_; }

 protected:
  const AudioSampleBuffer& buffer_;

  // Next position to deliver samples from.
  int position_;

  // Are we looping?
  bool looping_;

  DISALLOW_COPY_AND_ASSIGN(Buffered);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COMPUTED_H__
