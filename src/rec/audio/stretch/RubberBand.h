#ifndef __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
#define __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__

#include "rec/audio/SampleRate.h"
#include "rec/audio/stretch/Implementation.h"
#include "rec/audio/stretch/Stretch.h"

namespace RubberBand { class RubberBandStretcher; }

namespace rec {
namespace audio {
namespace stretch {

typedef ::RubberBand::RubberBandStretcher RubberBandStretcher;

class RubberBand : public Implementation {
 public:
  RubberBand(PositionableAudioSource* source, const Stretch& stretch);
  virtual ~RubberBand();

  virtual void setStretch(const Stretch&);
  virtual void setMasterTune(double detuneCents);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
  virtual void setSampleRate(int sampleRate);

 private:
  void stretchChanged();

  CriticalSection lock_;
  ptr<RubberBandStretcher> stretcher_;

  // TODO: this duplicates everything in strechy.h...!
 	int channels_;
  int sampleRate_;
  double timeRatio_;
  double pitchScale_;
  int maxProcessSize_;
  double detuneCents_;
  Stretch stretch_;

  int retrieve(int copied, const AudioSourceChannelInfo&);
  void process();

  DISALLOW_COPY_ASSIGN_AND_LEAKS(RubberBand);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_RUBBERBANDSTRETCHY__
