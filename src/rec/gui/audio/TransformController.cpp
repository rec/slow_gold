#include "rec/gui/audio/TransformController.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

static const bool ENABLE_SHIFTS = !false;

namespace rec {
namespace gui {
namespace audio {

using rec::audio::Gain;
using data::Address;

namespace {

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

}  // namespace

TransformController::TransformController()
    : Layout("TransformController", VERTICAL),
      playbackSpeed_("Speed", Address("time_percent")),
      pitchScale_("Pitch", Address("semitone_shift")),
      fineScale_("Tune", Address("detune_cents")) {
  playbackSpeed_.slider()->setRange(0.5, 200.0, 1.0);
  pitchScale_.slider()->setRange(-24.0, 24.0, 1.0);
  fineScale_.slider()->setRange(-50.0, 50.0, 1.0);

  playbackSpeed_.slider()->setDetent(100.0f);
  playbackSpeed_.slider()->setDetentRadius(0.008f);  // TODO: Why so small?
  pitchScale_.slider()->setDetent(0.0f);
  fineScale_.slider()->setDetent(0.0f);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");

  pitchScale_.setEnabled(ENABLE_SHIFTS);
  fineScale_.setEnabled(ENABLE_SHIFTS);

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.setTextWhenNothingSelected("Stereo");
  stereoComboBox_.setTextWhenNoChoicesAvailable("Stereo");
  stereoComboBox_.addItem("Stereo", STEREO);
  stereoComboBox_.addItem("Left", LEFT);
  stereoComboBox_.addItem("Right", RIGHT);
  stereoComboBox_.addItem("L + R", LEFT_PLUS_RIGHT);
  stereoComboBox_.addListener(this);

  addToLayout(&stereoComboBox_, 18);

  static const int SLIDER_HEIGHT = 18;
  addToLayout(&playbackSpeed_, SLIDER_HEIGHT);
  addToLayout(&pitchScale_, SLIDER_HEIGHT);
  addToLayout(&fineScale_, SLIDER_HEIGHT);
}

void TransformController::onDataChange(const Stretch& s) {
  MessageManagerLock l;
  playbackSpeed_.setEnabled(!s.time_disabled());
}

void TransformController::onDataChange(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  MessageManagerLock l;
  stereoComboBox_.setSelectedId(sides, true);
}

void TransformController::comboBoxChanged(juce::ComboBox* box) {
  if (box == &stereoComboBox_) {
    if (DataListener<StereoProto>::data()) {
      Sides sides = static_cast<Sides>(stereoComboBox_.getSelectedId());
      StereoProto stereo;
      if (sides != STEREO) {
        stereo.set_type(StereoProto::SINGLE);
        stereo.set_side(static_cast<StereoProto::Side>(sides - 2));
      }
      DataListener<StereoProto>::data()->setValue(stereo);
    }
  }
}


#if 0
                            public DataListener<rec::audio::Gain>,
  virtual void onDataChange(const rec::audio::Gain&);
  LevelMeter levelMeter_;
  DataSlider<rec::audio::Gain, double> level_;
  gui::SetterToggle<rec::audio::Gain> muteButton_;

  listener::Listener<const LevelVector&>* levelListener() { return &levelMeter_; }
  void clearLevels();
  LevelMeter* levelMeter() { return &levelMeter_; }


,
      level_("Gain", Address("gain")),
      muteButton_("Mute", Address("mute"))
  level_.slider()->setRange(-36.0, +12.0, 0.1);
  level_.slider()->setDetent(0.0f);
  level_.slider()->setTextValueSuffix(" dB");

  addToLayout(&muteButton_, 14);

  addToLayout(&level_, SLIDER_HEIGHT);
  addToLayout(&levelMeter_);

void TransformController::onDataChange(const rec::audio::Gain& gain) {
  MessageManagerLock mml;
  level_.slider()->setEnabled(!gain.mute());
  levelMeter_(gain);
}

void TransformController::clearLevels() {
  levelMeter_(LevelVector());
}

#endif

}  // namespace audio
}  // namespace gui
}  // namespace rec

