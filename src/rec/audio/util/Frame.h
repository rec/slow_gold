#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/Samples.h"
#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

template <typename Frame>
class Frames {
 public:
  Frames(Samples<44100> length = 0)
      : length_(-1), allocatedLength_(-1), frames_(NULL) {
    setLength(length);
  }
  ~Frames() { free(frames_); }

  bool setLength(Samples<44100> length, bool mustReallocate = false);
  Samples<44100> getAudioBlock(const Info& info, Samples<44100> offset) const;

  Frame* frames() { return frames_; }
  Samples<44100> length() const { return length_; }

 private:
  Samples<44100> length_, allocatedLength_;
  Frame* frames_;

  DISALLOW_COPY_AND_ASSIGN(Frames);
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
};

}  // namespace data
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FRAME__
