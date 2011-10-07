#include "rec/gui/audio/PlayerController.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;


static const bool ENABLE_SHIFTS = false;

namespace rec {

using audio::Gain;
using data::Address;

namespace gui {
namespace audio {

namespace {

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

}  // namespace


PlayerController::PlayerController()
    : Layout("PlayerController", VERTICAL),
      playbackSpeed_("Speed", Address("time_percent")),
      pitchScale_("Pitch", Address("semitone_shift")),
      fineScale_("Tune", Address("detune_cents")),
      level_("Gain", Address("gain")),
      disableButton_("Disable speed", Address("time_disabled")),
      zoomToSelectionButton_("Zoom to selection", Address("zoom_to_selection")),
      muteButton_("Mute", Address("mute")),
      dimButton_("Dim", Address("dim")) {
  playbackSpeed_.slider()->setRange(0, 200.0, 1.0);
  pitchScale_.slider()->setRange(-7.0, 7.0, 0.5);
  fineScale_.slider()->setRange(-50.0, 50.0, 1.0);
  level_.slider()->setRange(-60.0, +18.0, 0.1);

  playbackSpeed_.slider()->setDetent(100.0f);
  pitchScale_.slider()->setDetent(0.0f);
  fineScale_.slider()->setDetent(0.0f);
  level_.slider()->setDetent(0.0f);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");
  level_.slider()->setTextValueSuffix(" dB");

  pitchScale_.setEnabled(ENABLE_SHIFTS);
  fineScale_.setEnabled(ENABLE_SHIFTS);
  disableButton_.setEnabled(ENABLE_SHIFTS);
  zoomToSelectionButton_.setEnabled(false);

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.setTextWhenNothingSelected("Stereo");
  stereoComboBox_.setTextWhenNoChoicesAvailable("Stereo");
  stereoComboBox_.addItem("Stereo", STEREO);
  stereoComboBox_.addItem("Mono (Left + Right)", LEFT_PLUS_RIGHT);
  stereoComboBox_.addItem("Mono (Left)", LEFT);
  stereoComboBox_.addItem("Mono (Right)", RIGHT);
  stereoComboBox_.addListener(this);

  addToLayout(&modeSelector_, 24);
  addToLayout(&stereoComboBox_, 18);

  static const int SLIDER_HEIGHT = 18;
  addToLayout(&playbackSpeed_, SLIDER_HEIGHT);
  addToLayout(&pitchScale_, SLIDER_HEIGHT);
  addToLayout(&fineScale_, SLIDER_HEIGHT);

  addToLayout(&muteButton_, 14);
  addToLayout(&dimButton_, 14);
  addToLayout(&disableButton_, 14);
  addToLayout(&zoomToSelectionButton_, 14);

  addToLayout(&level_, SLIDER_HEIGHT);
  addToLayout(&levelMeter_);
}

void PlayerController::onDataChange(const Stretch& s) {
  MessageManagerLock l;
  enableSliders(!s.time_disabled());
}

void PlayerController::onDataChange(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  thread::callAsync(&stereoComboBox_, &juce::ComboBox::setSelectedId,
                    static_cast<int>(sides), true);
}

void PlayerController::onDataChange(const rec::audio::Gain& gain) {
  MessageManagerLock mml;
  bool mute = gain.mute();
  bool dim = gain.dim();
  level_.slider()->setEnabled(!(mute || dim));
  muteButton_.setEnabled(mute || !dim);
  dimButton_.setEnabled(!mute || dim);
}

void PlayerController::setData(persist::Data<Stretch>* d) {
  DataListener<Stretch>::setData(d);
  playbackSpeed_.setUntypedData(d);
  pitchScale_.setUntypedData(d);
  fineScale_.setUntypedData(d);
}

void PlayerController::setData(persist::Data<Gain>* d) {
  DataListener<Gain>::setData(d);
  level_.setUntypedData(d);
}

void PlayerController::comboBoxChanged(juce::ComboBox* box) {
  if (box == &stereoComboBox_) {
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
}

void PlayerController::setZoom(data::UntypedData* data) {
  zoomToSelectionButton_.setUntypedData(data);
}

void PlayerController::enableSliders(bool enabled) {
  playbackSpeed_.setEnabled(enabled && false);
}

void PlayerController::clearLevels() {
  levelMeter_(LevelVector());
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

