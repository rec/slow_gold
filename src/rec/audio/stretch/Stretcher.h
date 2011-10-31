#ifndef __REC_AUDIO_STRETCH_STRETCHER__
#define __REC_AUDIO_STRETCH_STRETCHER__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace stretch {

class Stretch;

class Stretcher {
 public:
  Stretcher(PositionableAudioSource* s) : source_(s) {}
  virtual ~Stretcher() {}

  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo&) = 0;
  virtual void setStretch(const Stretch&) = 0;

 protected:
  PositionableAudioSource* source() { return source_; }

 private:
  PositionableAudioSource* source_;
  DISALLOW_COPY_AND_ASSIGN(Stretcher);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_STRETCHER__
