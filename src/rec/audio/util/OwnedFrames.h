#ifndef __REC_AUDIO_UTIL_OWNEDFRAMES__
#define __REC_AUDIO_UTIL_OWNEDFRAMES__

#include "rec/base/base.h"

namespace rec {
namespace audio {

template <typename Frame>
class OwnedFrames {
 public:
  OwnedFrames(Samples<44100> length = 0, bool mustReallocate = false)
      : length_(-1),
        allocatedLength_(-1),
        frames_(NULL),
        mustReallocate_(mustReallocate) {
    setLength(length);
  }
  ~OwnedFrames() { free(frames_.frames_); }
  FramesBase<Frame>* frames() { return frames_; }

  bool setLength(Samples<44100> length) {
    if (length != length_ && (mustReallocate_ || length > allocatedLength_)) {
      allocatedLength_ = length;
      size_t size = static_cast<size_t>(sizeof(Frame) * length);
      frames_ = reinterpret_cast<Frame*>(reallocf(frames_, size));
    }
    bool success = !length || frames_;
    if (!success)
      LOG(ERROR) << "Couldn't setLength: " << length << ", " << frames_;
    length_ = length;

    return success;
  }

  Samples<44100> length() const { return frames_.length_; }
  void setMustReallocate(bool must) { mustReallocate_ = must; }

 private:
  Samples<44100> allocatedLength_;
  FramesBase<Frame> frames_;
  bool mustReallocate_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Frames);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_OWNEDFRAMES__
