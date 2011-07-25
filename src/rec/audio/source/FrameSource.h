#ifndef __REC_AUDIO_SOURCE_FRAMESOURCE__
#define __REC_AUDIO_SOURCE_FRAMESOURCE__

#include "rec/audio/util/Frame.h"

namespace rec {
namespace audio {
namespace source {

template <typename Sample, int CHANNELS>
class FrameSource : public PositionableAudioSource {
 public:
  explicit FrameSource(const Frames<Sample, CHANNELS>& b) : buffer_(b) {}
  virtual ~FrameSource() {}

  virtual void getNextAudioBlock(const Info& info) {
    Info i = info;
    while (i.numSamples > 0) {
      SamplePosition copied = buffer_.getAudioBlock(i, position_);
      if (!copied) {
        LOG(ERROR) << "No samples copied!";
        DCHECK(copied);
        return;
      }
      i.numSamples -= copied;
      i.startSample += copied;
      setNextReadPosition(position_ + copied);
    }
  }

  virtual int64 getTotalLength() const {
    ScopedLock l(lock_);
    return buffer_.length();
  }

  virtual void setNextReadPosition(int64 p) {
    position_ = mod(p, std::max(1LL, getTotalLength()));
  }

  virtual int64 getNextReadPosition() const { return position_; };
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }

  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}

 private:
  CriticalSection lock_;

  const Frames<Sample, CHANNELS>& buffer_;
  int64 position_;
  bool looping_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FrameSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_FRAMESOURCE__
