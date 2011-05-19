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
template <typename Sample = short, int CHANNELS = 2>
class GenericFillableBuffer : public block::Fillable {
 public:
  static const int DEFAULT_BLOCK_SIZE = 4096;

  GenericFillableBuffer(SampleTime s = DEFAULT_BLOCK_SIZE)
      : frames_(NULL), buffer(CHANNELS, s) {
    info_.buffer = &buffer_;
    info_.startSample = 0;
  }

  void setBlockSize(SampleTime s) {
    buffer_.setSize(CHANNELS, s);
  }

  void setSource(PositionableAudioSource* source) {
    SampleTime size = source->getTotalLength();
    setLength(size);
    frames_.set_size(size);
    source_.reset(source);
  }

  virtual block::Size doFillNextBlock(const Block& block) {
    AudioSourceChannelInfo info;
    int blockSize = static_cast<int>(getSize(block));
    info.numSamples = juce::jmin(blockSize, buffer_.getNumSamples());
    source_->setNextReadPosition(block.first);
    source_->getNextAudioBlock(info);

    // Now copy it to our frame buffer.
    for (SampleTime i = 0; i < info.numSamples; ++i) {
      Frame* frame = &frames_[block.first + i];
      for (int c = 0; i < CHANNELS; ++i) {
        convert(*buffer_.getSampleData(c, i), &(*frame)[c]
    }
    return block.first + info.numSamples;
  }

 protected:
  virtual void onFilled() { source_.reset(); }

 private:
  Frames<Sample, CHANNELS> frames_
  ptr<PositionableAudioSource> source_;
  AudioSampleBuffer buffer_;
  AudioSourceChannelInfo info_;

  DISALLOW_COPY_AND_ASSIGN(GenericFillableBuffer);

  friend class audio::source::BufferSource;
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__
