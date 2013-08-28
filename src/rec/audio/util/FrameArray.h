#ifndef __REC_AUDIO_SAMPLES__
#define __REC_AUDIO_SAMPLES__

#include "rec/base/SampleTime.h"

namespace rec {
namespace audio {

template <typename Frame>
struct FrameArray {
  SampleTime length_, allocatedLength_;
  Frame* frames_;

  FrameArray() : length_(0), allocatedLength_(0), frames_(nullptr) {}

  bool reallocate(SampleTime newLength) {
    if (newLength > allocatedLength_) {
      size_t size = static_cast<size_t>(sizeof(Frame) * newLength);
      void *f = realloc(frames_, size);
      if (!f)
        return false;
      frames_ = static_cast<Frame*>(f);
      allocatedLength_ = newLength;
    }
    return true;
  }

  bool deallocate() {
    free(frames_);
    frames_ = nullptr;
  }
};

class Reserve {
 public:
  Reserve(int c) : count_(c) { bytes_ = malloc(c); }
  ~Reserve() { free(bytes_); }

 private:
  void* bytes_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Reserve);
};

template <typename Frame>
SampleTime reallocateBest(FrameArray<Frame>* frames, SampleTime length,
                          double shrinkage) {
  DCHECK_GT(shrinkage, 0.0);
  DCHECK_LT(shrinkage, 1.0);
  while (frames->allocatedLength_ > length && !frames->reallocate(length))
    length = static_cast<int>(shrinkage * length);
  return length;
}

template <typename Frame>
SampleTime reallocateBest(vector<Frame>* frames, SampleTime length,
                          double shrinkage) {
  DCHECK_GT(shrinkage, 0.0);
  DCHECK_LT(shrinkage, 1.0);
  while (frames->allocatedLength_ > length && !frames->reallocate(length))
    length = static_cast<int>(shrinkage * length);
  return length;
}



}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SAMPLES__
