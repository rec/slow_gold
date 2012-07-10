#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/SampleTime.h"
#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

template <typename Frame>
class Frames {
 public:
  Frames(SampleTime length = 0);
  ~Frames() { free(frames_); }

  bool setLength(SampleTime length);
  SampleTime getAudioBlock(const Info& info, SampleTime offset) const;
  Frame* frames() { return frames_; }
  SampleTime length() const { return length_; }

 private:
  SampleTime length_, allocatedLength_;
  Frame* frames_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Frames);
};

template <typename Sample, int CHANNELS>
struct InterleavedFrame {
  Sample sample_[CHANNELS];
};

typedef InterleavedFrame<short, 2> CDFrame;
typedef Frames<CDFrame> CDFrames;

typedef InterleavedFrame<float, 2> FloatFrame;
typedef Frames<FloatFrame> FloatFrames;


template <typename Sample, int CHANNELS>
struct ParallelFrame {
  ParallelFrame() : channels_(CHANNELS), sample_(NULL) {}
  ParallelFrame(Sample** sample) : channels_(CHANNELS), sample_(sample) {}

  const int channels_;
  Sample** sample_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(ParallelFrame);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FRAME__
