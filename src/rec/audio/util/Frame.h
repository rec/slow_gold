1#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/SamplePosition.h"
#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

#if 0
template <typename Sample, int CHANNELS>
struct Frame {
 Sample sample_[CHANNELS];
};

template <typename S, typename T, int CHANNELS>
void convertFrame(const Frame<S, CHANNELS>& f, const Frame<T, CHANNELS>* t) {
  for (int i = 0; i < CHANNELS; ++i)
    convertSample(f.sample_[i], t + i);
}
#endif

template <typename Sample, int CHANNELS>
class Frames {
 public:
  struct Frame {
    Sample sample_[CHANNELS];
  };

  Frames() : length_(0), frames_(NULL) {}
  ~Frames() { free(frames_); }

  bool realloc(SamplePosition length) {
    ScopedLock l(lock_);
    if (void* frames = realloc(frames_, sizeof(Frame) * length)) {
      length_ = length;
      frames_ = frames;
      return true;
    }
    LOG(ERROR) << "Not enough memory, sample length: " << length;
    return false;
  }

  void getAudioBlock(const Info& info, SamplePosition offset) {
    ScopedLock l(lock_);

    float** channels = info.buffer->getArrayOfChannels();
    for (int i = 0; i < info.numSamples; ++i) {
      for (int c = 0; c < CHANNELS; ++c)
        convertSample(frames_[i + offset][c], channels[c] + info.startSample);
    }
  }

 private:
  CriticalSection lock_;
  SamplePosition length_;
  Frame* frames_;

  DISALLOW_COPY_AND_ASSIGN(Frames);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FRAME__
