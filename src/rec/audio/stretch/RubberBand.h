#ifndef __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
#define __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__

#include "rec/audio/stretch/Implementation.h"

namespace RubberBand { class RubberBandStretcher; }

namespace rec {
namespace audio {
namespace stretch {

class Stretch;

class RubberBand : public Implementation {
 public:
  RubberBand(PositionableAudioSource* source, const Stretch& stretch);
  virtual ~RubberBand();

  virtual void setStretch(const Stretch&);
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo& info);

 private:
  ptr< ::RubberBand::RubberBandStretcher > stretcher_;
  DISALLOW_COPY_AND_ASSIGN(RubberBand);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
