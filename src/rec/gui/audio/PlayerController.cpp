#include "rec/gui/audio/PlayerController.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

namespace rec {
namespace gui {
namespace audio {

namespace {

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

}  // namespace

PlayerController::PlayerController()
    : Layout("PlayerController", VERTICAL),
      playbackSpeed_("Playback speed", Address("time_percent")),
      pitchScale_("Transpose", Address("semitone_shift")),
      fineScale_("Fine tuning", Address("detune_cents")),
      disableButton_("Disable time shifting", Address("time_disabled")),
      zoomToSelectionButton_("Zoom to selection", Address("zoom_to_selection")),
      clickToZoomButton_("Click to zoom", Address("click_to_zoom")) {
  playbackSpeed_.slider()->setRange(0, 200.0, 1.0);
  pitchScale_.slider()->setRange(-7.0, 7.0, 0.5);
  fineScale_.slider()->setRange(-50.0, 50.0, 1.0);

  playbackSpeed_.slider()->setDetent(100.0);
  pitchScale_.slider()->setDetent(0.0);
  fineScale_.slider()->setDetent(0.0);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");

  addToLayout(&playbackSpeed_);
  addToLayout(&pitchScale_);
  addToLayout(&fineScale_);

  addToLayout(&gainController_);
  addToLayout(&levelMeter_);

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

void PlayerController::operator()(const Stretch& s) {
  thread::callAsync(this, &PlayerController::enableSliders, !s.time_disabled());
}

void PlayerController::operator()(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  thread::callAsync(&stereoComboBox_, &juce::ComboBox::setSelectedId,
                    static_cast<int>(sides), true);
}

void PlayerController::setData(persist::Data<Stretch>* data) {
  playbackSpeed_.setData(data);
  pitchScale_.setData(data);
  fineScale_.setData(data);
  disableButton_.setData(data);

  DataListener<Stretch>::setData(data);
}

void PlayerController::setData(persist::Data<StereoProto>* data) {
  DataListener<StereoProto>::setData(data);
}

void PlayerController::comboBoxChanged(juce::ComboBox*) {
  if (DataListener<StereoProto>::data_) {
    Sides sides = static_cast<Sides>(stereoComboBox_.getSelectedId());
    StereoProto stereo;
    if (sides != STEREO) {
      stereo.set_type(StereoProto::SINGLE);
      stereo.set_side(static_cast<StereoProto::Side>(sides - 2));
    }
    data::set(DataListener<StereoProto>::data_, stereo);
  }
}

void PlayerController::setZoom(data::UntypedData* data) {
  zoomToSelectionButton_.setData(data);
  clickToZoomButton_.setData(data);
}

void PlayerController::enableSliders(bool enabled) {
  playbackSpeed_.setEnabled(enabled);
  // pitchScale_.setEnabled(enabled);
  // fineScale_.setEnabled(enabled);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

