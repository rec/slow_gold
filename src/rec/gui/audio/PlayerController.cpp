#include "rec/gui/audio/PlayerController.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

static const bool DISABLE_SHIFTS = true;

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

  playbackSpeed_.slider()->setDetent(100.0);
  pitchScale_.slider()->setDetent(0.0);
  fineScale_.slider()->setDetent(0.0);
  level_.slider()->setDetent(0.0);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");
  level_.slider()->setTextValueSuffix(" dB");

  addToLayout(&playbackSpeed_);
  addToLayout(&pitchScale_);
  addToLayout(&fineScale_);
  addToLayout(&level_);
  addToLayout(&levelMeter_);

  pitchScale_.setEnabled(DISABLE_SHIFTS);
  fineScale_.setEnabled(DISABLE_SHIFTS);
  disableButton_.setEnabled(DISABLE_SHIFTS);

  addToLayout(&muteButton_, 14);
  addToLayout(&dimButton_, 14);
  addToLayout(&disableButton_, 14);
  addToLayout(&zoomToSelectionButton_, 14);
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

  addToLayout(&stereoComboBox_, 14);

  modeComboBox_.setEditableText(false);
  modeComboBox_.setJustificationType(Justification::centredLeft);
  modeComboBox_.setTextWhenNothingSelected("Mode");
  modeComboBox_.setTextWhenNoChoicesAvailable("Mode");

  modeComboBox_.addItem("Drag", Mode::DRAG);
  modeComboBox_.addItem("Draw loop points", Mode::DRAW_LOOP_POINTS);
  modeComboBox_.addItem("Jump to time", Mode::SET_TIME);
  modeComboBox_.addItem("Toggle segment selection", Mode::TOGGLE_SELECTION);
  modeComboBox_.addItem("Zoom in", Mode::ZOOM_IN);
  modeComboBox_.addItem("Zoom out", Mode::ZOOM_OUT);
  modeComboBox_.addListener(this);

  addToLayout(&modeComboBox_, 14);
}

void PlayerController::setData(persist::Data<Stretch>* data) {
  playbackSpeed_.setData(data);
  pitchScale_.setData(data);
  fineScale_.setData(data);
  disableButton_.setData(data);

  DataListener<Stretch>::setData(data);
}

void PlayerController::operator()(const Stretch& s) {
  thread::callAsync(this, &PlayerController::enableSliders, !s.time_disabled());
}

void PlayerController::setData(persist::Data<StereoProto>* data) {
  DataListener<StereoProto>::setData(data);
}

void PlayerController::operator()(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  thread::callAsync(&stereoComboBox_, &juce::ComboBox::setSelectedId,
                    static_cast<int>(sides), true);
}

void PlayerController::setData(persist::Data<rec::audio::Gain>* data) {
  muteButton_.setData(data);
  dimButton_.setData(data);
  level_.setData(data);

  DataListener<rec::audio::Gain>::setData(data);
}

void PlayerController::operator()(const rec::audio::Gain& gain) {
  juce::MessageManagerLock mml;
  bool mute = gain.mute();
  bool dim = gain.dim();
  level_.slider()->setEnabled(!(mute || dim));
  muteButton_.setEnabled(mute || !dim);
  dimButton_.setEnabled(!mute || dim);
}

void PlayerController::setData(persist::Data<Mode>* data) {
  DataListener<Mode>::setData(data);
}

void PlayerController::operator()(const Mode& mode) {
  juce::MessageManagerLock l;
  modeComboBox_.setSelectedId(mode.click(), true);
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

  } else if (box == &modeComboBox_) {
    if (DataListener<Mode>::data_) {
      Mode mode;
      mode.set_click(static_cast<Mode::Action>(modeComboBox_.getSelectedId()));
      data::set(DataListener<Mode>::data_, mode);
    }
  }
}

void PlayerController::setZoom(data::UntypedData* data) {
  zoomToSelectionButton_.setData(data);
}

void PlayerController::enableSliders(bool enabled) {
  playbackSpeed_.setEnabled(enabled && false);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

