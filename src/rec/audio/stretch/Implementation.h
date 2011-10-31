#ifndef __REC_AUDIO_STRETCH_IMPLEMENTATION__
#define __REC_AUDIO_STRETCH_IMPLEMENTATION__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace stretch {

class Stretch;

class Implementation {
 public:
  Implementation(PositionableAudioSource* s) : source_(s) {}
  virtual ~Implementation() {}

  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo&) = 0;
  virtual void setStretch(const Stretch&) = 0;

 protected:
  PositionableAudioSource* source() { return source_; }

 private:
  PositionableAudioSource* source_;
  DISALLOW_COPY_AND_ASSIGN(Implementation);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_IMPLEMENTATION__
