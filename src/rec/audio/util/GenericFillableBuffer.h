#ifndef __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__
#define __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__

#include "rec/util/listener/Listener.h"
#include "rec/util/block/Fillable.h"
#include "rec/audio/util/Frame.h"

namespace rec {
namespace audio {

namespace source { class BufferSource; }

namespace util {

// Stores two 16-bit samples in each word!
template <typename Sample, int CHANNELS>
class GenericFillableBuffer : public block::Fillable {
 public:
  static const int DEFAULT_BLOCK_SIZE = 4096;

  GenericFillableBuffer(SampleTime s = DEFAULT_BLOCK_SIZE)
      : frames_(NULL), buffer_(CHANNELS, s) {
    info_.buffer = &buffer_;
    info_.startSample = 0;
  }
  virtual ~GenericFillableBuffer() {}

  void setBlockSize(SampleTime s) {
    buffer_.setSize(CHANNELS, s);
  }

  void setSource(PositionableAudioSource* source) {
    ScopedLock l(lock_);

    SampleTime size = source->getTotalLength();
    setLength(size);
    frames_.resize(size);
    source_.reset(source);
  }

  virtual block::Size doFillNextBlock(const block::Block& b) {
    ScopedLock l(lock_);
    int blockSize = static_cast<int>(block::getSize(b));
    info_.numSamples = juce::jmin(blockSize, buffer_.getNumSamples());
    source_->setNextReadPosition(b.first);
    source_->getNextAudioBlock(info_);

    // Now copy it to our frame buffer.
    for (SampleTime i = 0; i < info_.numSamples; ++i) {
      Frame<Sample, CHANNELS>* frame = &frames_[b.first + i];
      for (int c = 0; c < CHANNELS; ++c)
        convertSample(*buffer_.getSampleData(c, i), &frame->sample_[c]);
    }
    return b.first + info_.numSamples;
  }

  const Frames<Sample, CHANNELS>& frames() const { return frames_; }

 protected:
  // TODO:  re-enable this?
  // virtual void onFilled() { source_.reset(); }

 private:
  Frames<Sample, CHANNELS> frames_;
  ptr<PositionableAudioSource> source_;
  AudioSampleBuffer buffer_;
  AudioSourceChannelInfo info_;

  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(GenericFillableBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__
