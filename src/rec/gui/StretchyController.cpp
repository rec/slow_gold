#include "rec/gui/StretchyController.h"

namespace rec {
namespace gui {

StretchyController::StretchyController()
    : Layout(VERTICAL, true, "StretchyController"),
      disableButton_("Disable", Address("disabled")),
      playbackSpeed_("Playback speed", Address("time_percent")),
      pitchScale_("Transpose", Address("semitone_shift")),
      fineScale_("Fine tuning", Address("detune_cents")) {
  playbackSpeed_.slider()->setRange(0, 200.0, 1.0);
  pitchScale_.slider()->setRange(-7.0, 7.0, 0.5);
  fineScale_.slider()->setRange(-50.0, 50.0, 1.0);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");

  addToLayout(&disableButton_);
  addToLayout(&playbackSpeed_);
  addToLayout(&pitchScale_);
  addToLayout(&fineScale_);
}

void StretchyController::setData(persist::Data<StretchyProto>* data) {
  playbackSpeed_.setData(data);
  pitchScale_.setData(data);
  fineScale_.setData(data);
  disableButton_.setData(data);

  bool enable = !(data && data->get().disabled());
  thread::callAsync(this, &StretchyController::enableSliders, enable);
}

void StretchyController::enableSliders(bool enabled) {
  playbackSpeed_.setEnabled(enabled);
  pitchScale_.setEnabled(enabled);
  fineScale_.setEnabled(enabled);
}

}  // namespace gui
}  // namespace rec

