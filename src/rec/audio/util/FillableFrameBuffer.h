#ifndef __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
#define __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__

#include "rec/base/Samples.h"
#include "rec/audio/util/Frame.h"
#include "rec/util/block/Fillable.h"
#include "rec/util/Listener.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
class FillableFrameBuffer : public block::Fillable {
 public:
  const static int BLOCK_SIZE = 40960;

  FillableFrameBuffer(int blockSize = BLOCK_SIZE);
  virtual ~FillableFrameBuffer() {}

  // Returns the length in samples, or 0 if there's an error.
  Samples<44100> setReader(AudioFormatReader* reader);
  virtual block::Size doFillNextBlock(const block::Block& b);

  typedef Frames<InterleavedFrame<Sample, CHANNELS> > FillableFrame;

  const FillableFrame& frames() const { return frames_; }

 protected:
  virtual void onFilled() { reader_.reset(); }

 private:
  CriticalSection lock_;

  const block::Size blockSize_;
  FillableFrame frames_;
  ptr<AudioFormatReader> reader_;
  vector<int> buffer_[CHANNELS];
  int* bufferPointers_[CHANNELS];

  DISALLOW_COPY_AND_ASSIGN(FillableFrameBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
