#include "rec/gui/StretchyController.h"

namespace rec {
namespace gui {

StretchyController::StretchyController()
    : Layout("StretchyController", VERTICAL),
      playbackSpeed_("Playback speed", Address("stretchy", "time_percent")),
      pitchScale_("Transpose", Address("stretchy", "semitone_shift")),
      fineScale_("Fine tuning", Address("stretchy", "detune_cents")),
      disableButton_("Disable pitch and time shifting",
                     Address("stretchy", "disabled")) {
  playbackSpeed_.slider()->setRange(0, 200.0, 1.0);
  pitchScale_.slider()->setRange(-7.0, 7.0, 0.5);
  fineScale_.slider()->setRange(-50.0, 50.0, 1.0);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");

  addToLayout(&playbackSpeed_);
  addToLayout(&pitchScale_);
  addToLayout(&fineScale_);
  addToLayout(&disableButton_, 14);
}

void StretchyController::setData(UntypedData* data) {
  playbackSpeed_.setData(data);
  pitchScale_.setData(data);
  fineScale_.setData(data);
  disableButton_.setData(data);

  audio::stretch::StretchyLoop proto;
  bool enable = !(data && data->fill(&proto) && proto.stretchy().disabled());
  thread::callAsync(this, &StretchyController::enableSliders, enable);
}

void StretchyController::enableSliders(bool enabled) {
  playbackSpeed_.setEnabled(enabled);
  pitchScale_.setEnabled(enabled);
  fineScale_.setEnabled(enabled);
}

}  // namespace gui
}  // namespace rec

