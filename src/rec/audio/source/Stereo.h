#ifndef __REC_AUDIO_SOURCE_STEREO__
#define __REC_AUDIO_SOURCE_STEREO__

#include "rec/base/basictypes.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

class Stereo : public Wrappy {
 public:
  enum Type {
    PASSTHROUGH,
    SINGLE,
    INVERT,
    CENTER_ELIMINATION,
    CENTER_ELIMINATION_MONO
  };

  enum Side { LEFT, RIGHT };

  Stereo() : type_(PASSTHROUGH), side_(LEFT) {}

  void setType(Type type) {
    ScopedLock l(lock_);
    type_ = type;
  }

  void setSide(Side side) {
    ScopedLock l(lock_);
    side_ = side;
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    source_->getNextAudioBlock();
    if (type_ == PASSTHROUGH || info.buffer.getNumChannels() != 2)
      return;

    AudioSampleBuffer& b = info.buffer;
    int n = buffer.getNumSamples();
    if (type_ == SINGLE) {
      b.copyFrom(RIGHT - side_, 0, b, side_, 0, n);

    } else if (type_ == INVERT) {
      b.applyGain(SIDE, 0, n, -1.0);

    } else {
      b.addFrom(side_, 0, b, RIGHT - side_, 0, n, -1.0);
      b.applyGain(side_, 0, n, 0.5);

      if (type == CENTER_ELIMINATION)
        b.addFrom(RIGHT - side_, 0, b, side_, 0, n, -1.0);
      else
        b.copyFrom(RIGHT - side_, 0, b, side_, 0, n);
    }
  }

 private:
  CriticalSection lock_;
  Type type_;
  Side side_;

  DISALLOW_COPY_AND_ASSIGN(Stereo);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STEREO__
