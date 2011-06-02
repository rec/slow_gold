#include "rec/gui/audio/GainController.h"
#include "rec/audio/util/Gain.h"

namespace rec {
namespace gui {
namespace audio {

GainController::GainController()
    : Layout("GainController", VERTICAL),
      level_("Gain", Address("gain")),
      muteButton_("Mute", Address("mute")),
      dimButton_("Dim", Address("dim")) {
  level_.slider()->setRange(-60.0, +18.0, 0.1);
  level_.slider()->setDetent(0.0);
  addToLayout(&level_);
  addToLayout(&muteButton_, 14);
  addToLayout(&dimButton_, 14);
}

void GainController::setData(persist::Data<rec::audio::Gain>* data) {
  level_.setData(data);
  muteButton_.setData(data);
  dimButton_.setData(data);

  DataListener<rec::audio::Gain>::setData(data);
}

void GainController::operator()(const rec::audio::Gain& gain) {
  juce::MessageManagerLock mml;
  level_.slider()->setEnabled(!(gain.mute() || gain.dim()));
}

}  // namespace audio
}  // namespace gui
}  // namespace rec