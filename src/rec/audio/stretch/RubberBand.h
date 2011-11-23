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
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 private:
  CriticalSection lock_;
  ptr< ::RubberBand::RubberBandStretcher> stretcher_;
 	int channels_;
  double timeRatio_;
  double pitchScale_;
  int chunkSize_;
  int maxProcessSize_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(RubberBand);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
