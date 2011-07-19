#ifndef __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__
#define __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__

#include "rec/base/SamplePosition.h"
#include "rec/audio/util/Frame.h"
#include "rec/util/block/Fillable.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
class GenericFillableBuffer : public block::Fillable {
 public:
  const static int BLOCK_SIZE = 4096;

  GenericFillableBuffer(int blockSize = BLOCK_SIZE) : blockSize_(blockSize) {
    for (int i = 0; i < CHANNELS; ++i) {
      buffer_[i].set_size(blockSize);
      bufferPointers_[i] = &buffer_[i][0];
    }
  }

  virtual ~GenericFillableBuffer() {}

  bool setReader(AudioFormatReader* reader);
  virtual block::Size doFillNextBlock(const block::Block& b);
  const Frames<Sample, CHANNELS>& frames() const { return frames_; }

 protected:
  virtual void onFilled() { source_.reset(); }

 private:
  void setBlockSize(SamplePosition s) { buffer_.setSize(CHANNELS, s); }

  CriticalSection lock_;

  const SamplePosition blockSize_;
  Frames<Sample, CHANNELS> frames_;
  ptr<AudioFormatReader> reader_;
  vector<int> buffer_[CHANNELS];
  int* bufferPointers_[CHANNELS];

  DISALLOW_COPY_AND_ASSIGN(GenericFillableBuffer);
};


// Implementation
//

template <typename Sample, int CHANNELS>
bool GenericFillableBuffer::setReader(AudioFormatReader* reader) {
  ScopedLock l(lock_);

  SamplePosition size = source->getTotalLength();
  if (!frames_.realloc(size))
    return false;

  setLength(size);
  reader_.reset(reader);
  filled_.clear();
  return true;
}

template <typename Sample, int CHANNELS>
block::Size Generic::doFillNextBlock(const block::Block& b) {
  ScopedLock l(lock_);

  if (!reader_) {
    LOG(ERROR) << "No reader!";
    return 0;
  }

  SamplePosition size = std::min(block::getSize(b), blockSize_);
  if (!reader->read(bufferPointers_, CHANNELS, b.begin, size, false)) {
    LOG(ERROR) << "Reader failed to read!";
    return 0;
  }

  for (int i = 0; i < size; ++i) {
    for (int c = 0; c < CHANNELS; ++c)
      copySample(bufferPointers_[c][i], frames_.frame()[i] + c);
  }

  return size;
}

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__
