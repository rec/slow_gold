#ifndef __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
#define __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__

#include "rec/audio/stretch/Stretcher.h"

namespace RubberBand { class RubberBandStretcher; }

namespace rec {
namespace audio {
namespace stretch {

class Stretch;

class RubberbandStretchy : public Stretcher {
 public:
  RubberbandStretchy(PositionableAudioSource* source, const Stretch& stretch);
  virtual ~RubberbandStretchy();

  virtual void setStretch(const Stretch&);
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo& info);

 private:
  ptr<RubberBand::RubberBandStretcher> stretcher_;
  DISALLOW_COPY_AND_ASSIGN(RubberbandStretchy);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
