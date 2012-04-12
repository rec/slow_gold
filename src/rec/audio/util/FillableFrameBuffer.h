#ifndef __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
#define __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__

#include "rec/audio/util/Frame.h"
#include "rec/base/Samples.h"
#include "rec/util/block/Fillable.h"
#include "rec/util/Listener.h"

namespace rec {
namespace audio {
namespace util {

// Skin
const static int FILLABLE_FRAME_BLOCK_SIZE = 10240;

template <typename Sample, int CHANNELS>
struct SampleBuffer {
  SampleBuffer(int sampleCount) {
    for (int i = 0; i < CHANNELS; ++i) {
      buffer_[i].resize(sampleCount);
      pointers_[i] = &buffer_[i][0];
    }
  }

  vector<Sample> buffer_[CHANNELS];
  Sample* pointers_[CHANNELS];
};

template <typename Sample, int CHANNELS>
class FillableFrameBuffer : public block::Fillable {
 public:
  FillableFrameBuffer(int blockSize = FILLABLE_FRAME_BLOCK_SIZE);
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

  SampleBuffer<int32, CHANNELS> intBuffer_;
  SampleBuffer<float, CHANNELS> floatBuffer_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillableFrameBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
