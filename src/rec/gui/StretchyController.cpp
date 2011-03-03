#include "rec/gui/StretchyController.h"

namespace rec {
namespace gui {

namespace {

enum Sides {
  STEREO = 1, LEFT_PLUS_RIGHT, LEFT, RIGHT
};

}  // namespace

StretchyController::StretchyController()
    : Layout("StretchyController", VERTICAL),
      playbackSpeed_("Playback speed", Address("stretch", "time_percent")),
      pitchScale_("Transpose", Address("stretch", "semitone_shift")),
      fineScale_("Fine tuning", Address("stretch", "detune_cents")),
      disableButton_("Disable pitch and time shifting",
                     Address("stretch", "disabled")),
      zoomToSelectionButton_("Zoom to selection",
                             Address("zoom_to_selection")),
      clickToZoomButton_("Click to zoom",
                         Address("click_to_zoom")) {
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
  addToLayout(&zoomToSelectionButton_, 14);
  addToLayout(&clickToZoomButton_, 14);
  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.setTextWhenNothingSelected("Stereo");
  stereoComboBox_.setTextWhenNoChoicesAvailable("Stereo");
  stereoComboBox_.addItem("Stereo", STEREO);
  stereoComboBox_.addItem("Mono (Left + Right)", LEFT_PLUS_RIGHT);
  stereoComboBox_.addItem("Mono (Left)", LEFT);
  stereoComboBox_.addItem("Mono (Right)", RIGHT);
  stereoComboBox_.addListener(this);
  addToLayout(&stereoComboBox_, 14);
}

void StretchyController::setData(UntypedData* data) {
  playbackSpeed_.setData(data);
  pitchScale_.setData(data);
  fineScale_.setData(data);
  disableButton_.setData(data);

  audio::stretch::StretchLoop proto;
  bool enable = !(data && data->fill(&proto) && proto.stretch().disabled());
  thread::callAsync(this, &StretchyController::enableSliders, enable);
}

void StretchyController::setZoom(UntypedData* data) {
  zoomToSelectionButton_.setData(data);
  clickToZoomButton_.setData(data);
}

void StretchyController::enableSliders(bool enabled) {
  playbackSpeed_.setEnabled(enabled);
  pitchScale_.setEnabled(enabled);
  fineScale_.setEnabled(enabled);
}

}  // namespace gui
}  // namespace rec

