#include "rec/gui/audio/TransformController.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

static const bool ENABLE_SHIFTS = !false;
static const int SLIDER_HEIGHT = 18;
static const int LEFT_PANEL_WIDTH = 100;

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
    : Layout("TransformController", HORIZONTAL),
      playbackSpeed_("Speed", Address("time_percent")),
      pitchScale_("Pitch", Address("semitone_shift")),
      fineScale_("Tune", Address("detune_cents")),
      enableButton_("Transform", Address("enabled")),
      leftPanel_("Left", VERTICAL),
      rightPanel_("Right", VERTICAL) {
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

  leftPanel_.addToLayout(&enableButton_, SLIDER_HEIGHT);
  leftPanel_.addToLayout(&stereoComboBox_, SLIDER_HEIGHT);
  leftPanel_.addToLayout(&leftPadding_);

  addToLayout(&leftPanel_, LEFT_PANEL_WIDTH);

  rightPanel_.addToLayout(&playbackSpeed_, SLIDER_HEIGHT);
  rightPanel_.addToLayout(&pitchScale_, SLIDER_HEIGHT);
  rightPanel_.addToLayout(&fineScale_, SLIDER_HEIGHT);
  rightPanel_.addToLayout(&rightPadding_);

  addToLayout(&rightPanel_, 150, -1.0, 250);
}

void TransformController::onDataChange(const Stretch& s) {
  MessageManagerLock l;
  playbackSpeed_.setEnabled(s.enabled());
  pitchScale_.setEnabled(s.enabled());
  fineScale_.setEnabled(s.enabled());
  stereoComboBox_.setEnabled(s.enabled());
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

}  // namespace audio
}  // namespace gui
}  // namespace rec

