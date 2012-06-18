#include "rec/audio/source/FrameSource.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/audio/util/Frame.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace audio {
namespace util {

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
class BufferedReaderImpl : public BufferedReader {
 public:
  BufferedReaderImpl(int s);
  virtual ~BufferedReaderImpl() {}

  // Returns the length in samples, or 0 if there's an error.
  virtual block::Size doFillNextBlock(const block::Block& b);
  typedef Frames<InterleavedFrame<Sample, CHANNELS> > FillableFrame;

  virtual Source* makeSource() const;
  virtual bool setLength(int64 length);

  const FillableFrame& frames() const { return frames_; }

 protected:
  virtual void onFilled() { reader_.reset(); }

 private:
  CriticalSection lock_;

  const block::Size blockSize_;
  FillableFrame frames_;

  SampleBuffer<int32, CHANNELS> intBuffer_;
  SampleBuffer<float, CHANNELS> floatBuffer_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BufferedReaderImpl);
};

const static int FILLABLE_FRAME_BLOCK_SIZE = 10240;

template <typename Sample, int CHANNELS>
BufferedReader* makeBufferedReader(int size = FILLABLE_FRAME_BLOCK_SIZE);

}  // namespace util
}  // namespace audio
}  // namespace rec

