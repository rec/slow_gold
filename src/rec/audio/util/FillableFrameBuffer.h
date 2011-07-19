#ifndef __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
#define __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__

#include "rec/base/SamplePosition.h"
#include "rec/audio/util/Frame.h"
#include "rec/util/block/Fillable.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
class FillableFrameBuffer : public block::Fillable {
 public:
  const static int BLOCK_SIZE = 4096;

  FillableFrameBuffer(int blockSize = BLOCK_SIZE);
  virtual ~FillableFrameBuffer() {}

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

  DISALLOW_COPY_AND_ASSIGN(FillableFrameBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
