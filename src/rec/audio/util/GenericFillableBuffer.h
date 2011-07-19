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

  GenericFillableBuffer(int blockSize = BLOCK_SIZE);
  virtual ~GenericFillableBuffer() {}

  bool setReader(AudioFormatReader* reader);
  virtual block::Size doFillNextBlock(const block::Block& b);
  const Frames<Sample, CHANNELS>& frames() const { return frames_; }

 protected:
  virtual void onFilled() { reader_.reset(); }

 private:
  CriticalSection lock_;

  const block::Size blockSize_;
  Frames<Sample, CHANNELS> frames_;
  ptr<AudioFormatReader> reader_;
  vector<int> buffer_[CHANNELS];
  int* bufferPointers_[CHANNELS];

  DISALLOW_COPY_AND_ASSIGN(GenericFillableBuffer);
};


}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_GENERIC_FILLABLE_BUFFER__
