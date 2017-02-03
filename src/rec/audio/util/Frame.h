#pragma once

#include "rec/base/SampleTime.h"
#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

template <typename Sample, int CHANNELS>
struct InterleavedFrame {
  Sample sample_[CHANNELS];
};

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

}  // namespace data
}  // namespace rec

