#include "rec/audio/stretch/SoundTouchStretchy.h"
#include "rec/audio/soundtouch/SoundTouch.h"

namespace rec {
namespace audio {
namespace stretch {

using soundtouch::SoundTouch;

namespace {

class SoundTouchStretchy : public source::Stretchy {
 public:
  SoundTouchStretchy(PositionableAudioSource* s, const Stretch& stretch)
      : Stretchy(s, stretch) {
  }

  void initializeStretcher() {
    soundTouch_.reset(new SoundTouch);
    soundTouch_->setRate(static_cast<float>(timeScale(stretch_)));
    soundTouch_->setChannels(stretch_.channels());
    soundTouch_->setPitch(pitchScale(stretch_));
  }

  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo&) {}

 private:
  ptr<SoundTouch> soundTouch_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SoundTouchStretchy);
};

}  // namespace

source::Stretchy* createSoundTouchStretchy(PositionableAudioSource* p,
                                           const Stretch& s) {
  return new SoundTouchStretchy(p, s);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

