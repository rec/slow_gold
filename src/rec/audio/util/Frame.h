#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/SamplePosition.h"
#include "rec/audio/Audio.h"

namespace rec {
namespace audio {


template <typename Sample, int CHANNELS>
struct Frame {
  Sample sample_[CHANNELS];
};

template <typename Frame>
class AbstractFrames {
 public:
  AbstractFrames() : length_(0), frames_(NULL) {}
  ~AbstractFrames() { free(frames_); }

  bool setLength(SamplePosition length);
  SamplePosition getAudioBlock(const Info& info, SamplePosition offset) const;

  Frame* frames() { return frames_; }
  SamplePosition length() const { return length_; }

 private:
  SamplePosition length_;
  Frame* frames_;

  DISALLOW_COPY_AND_ASSIGN(AbstractFrames);
};

template <typename Sample, int CHANNELS>
class Frames {
 public:
  typedef Frame<Sample, CHANNELS> Frame;

  Frames() : length_(0), frames_(NULL) {}
  ~Frames() { free(frames_); }

  bool setLength(SamplePosition length);
  SamplePosition getAudioBlock(const Info& info, SamplePosition offset) const;

  Frame* frames() { return frames_; }
  SamplePosition length() const { return length_; }

 private:
  SamplePosition length_;
  Frame* frames_;

  DISALLOW_COPY_AND_ASSIGN(Frames);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FRAME__
