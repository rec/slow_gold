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

  strategyComboBox_.setEditableText(false);
  strategyComboBox_.setJustificationType(Justification::centredLeft);
  strategyComboBox_.setTextWhenNothingSelected("Strategy");
  strategyComboBox_.setTextWhenNoChoicesAvailable("Strategy");
  strategyComboBox_.addItem("Audio Magic", Stretch::AUDIO_MAGIC);
  strategyComboBox_.addItem("SoundTouch", Stretch::SOUNDTOUCH);
  //strategyComboBox_.addListener(this);

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

#define ALLOWING_TIME_CHANGES false

void PlayerController::onDataChange(const Stretch& s) {
  MessageManagerLock l;
  playbackSpeed_.setEnabled(ALLOWING_TIME_CHANGES && !s.time_disabled());
  strategyComboBox_.setSelectedId(static_cast<int>(s.strategy()), true);
}

void PlayerController::onDataChange(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  MessageManagerLock l;
  stereoComboBox_.setSelectedId(sides, true);
}

void PlayerController::onDataChange(const rec::audio::Gain& gain) {
  MessageManagerLock mml;
  bool mute = gain.mute();
  bool dim = gain.dim();
  level_.slider()->setEnabled(!(mute || dim));
  muteButton_.setEnabled(mute || !dim);
  dimButton_.setEnabled(!mute || dim);
}

void PlayerController::setData(persist::TypedEditable<Stretch>* d) {
  DataListener<Stretch>::setData(d);
  playbackSpeed_.setUntypedEditable(d);
  pitchScale_.setUntypedEditable(d);
  fineScale_.setUntypedEditable(d);
}

void PlayerController::setData(persist::TypedEditable<Gain>* d) {
  DataListener<Gain>::setData(d);
  level_.setUntypedEditable(d);
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
      DataListener<StereoProto>::data_->set(stereo);
    }
  }
}

void PlayerController::setZoom(data::UntypedEditable* data) {
  zoomToSelectionButton_.setUntypedEditable(data);
}

void PlayerController::clearLevels() {
  levelMeter_(LevelVector());
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

