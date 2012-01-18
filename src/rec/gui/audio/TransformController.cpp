#include "rec/gui/audio/TransformController.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

namespace rec {
namespace gui {
namespace audio {

// TODO: i18n

using rec::audio::Gain;
using data::Address;

namespace {

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

const int SLIDER_HEIGHT = 30;
const int LEFT_PANEL_WIDTH = 90;
const int ENABLE_BUTTON_HEIGHT = 40;
const int COMBO_BOX_HEIGHT = 30;

const char* const PITCH_BUTTON_TEXT = "Pitch";
const char* const SPEED_BUTTON_TEXT = "Speed";
const char* const TRANSFORM_BUTTON_TEXT = "Transform";
const char* const TUNE_BUTTON_TEXT = "Tune";

const char* const STEREO_TEXT = "Stereo";
const char* const LEFT_TEXT = "Left";
const char* const RIGHT_TEXT = "Right";
const char* const LEFT_PLUS_RIGHT_TEXT = "L + R";

const char* const SEMITONES_TEXT = " semitones";
const char* const CENTS_TEXT = " cents";

}  // namespace

using rec::audio::stretch::Stretch;

TransformController::TransformController()
    : Layout("TransformController", HORIZONTAL),
      playbackSpeed_(SPEED_BUTTON_TEXT, getTypeName<Stretch>(),
                     Address("time_percent")),
      pitchScale_(PITCH_BUTTON_TEXT, getTypeName<Stretch>(),
                  Address("semitone_shift")),
      fineScale_(TUNE_BUTTON_TEXT, getTypeName<Stretch>(),
                 Address("detune_cents")),
      enableButton_(TRANSFORM_BUTTON_TEXT, getTypeName<Stretch>(),
                    Address("enabled")),
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
  pitchScale_.slider()->setTextValueSuffix(SEMITONES_TEXT);
  fineScale_.slider()->setTextValueSuffix(CENTS_TEXT);

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.setTextWhenNothingSelected(STEREO_TEXT);
  stereoComboBox_.setTextWhenNoChoicesAvailable(STEREO_TEXT);
  stereoComboBox_.addItem(STEREO_TEXT, STEREO);
  stereoComboBox_.addItem(LEFT_TEXT, LEFT);
  stereoComboBox_.addItem(RIGHT_TEXT, RIGHT);
  stereoComboBox_.addItem(LEFT_PLUS_RIGHT_TEXT, LEFT_PLUS_RIGHT);
  stereoComboBox_.addListener(this);

  playbackSpeed_.setTooltip("Playback Speed Slider: "
                            "Controls how fast the loop plays back: "
                            "higher numbers mean the loop plays back faster.");
  pitchScale_.setTooltip("Playback Tuning Slider: "
                         "Tune loop playback up and down in pitch, "
                         "measured in semitones.");
  fineScale_.setTooltip("Playback Fine Tuning Slider: "
                        "Tune loop up or down in pitch, measured in "
                        "cents (1/100 of a semitone.");
  stereoComboBox_.setTooltip("Stereo Processing Menu:  choose between the "
                             "original stereo, just the left channel, "
                             "just the right channel, "
                             "or a mono mix of both channels.");
  enableButton_.setTooltip("Transform Enable Button: "
                           "Disable or enable all sound transformations: "
                           "pitch, time and stereo processing.");

  leftPanel_.addToLayout(&enableButton_, ENABLE_BUTTON_HEIGHT);
  leftPanel_.addToLayout(&stereoComboBox_, COMBO_BOX_HEIGHT);
  leftPanel_.addToLayout(&leftPadding_);

  addToLayout(&leftPanel_, LEFT_PANEL_WIDTH);

  rightPanel_.addToLayout(&playbackSpeed_, SLIDER_HEIGHT);
  rightPanel_.addToLayout(&pitchScale_, SLIDER_HEIGHT);
  rightPanel_.addToLayout(&fineScale_, SLIDER_HEIGHT);
  rightPanel_.addToLayout(&rightPadding_);

  addToLayout(&rightPanel_, 150, -1.0, 250);
}

TransformController::~TransformController() {}

void TransformController::startListening() {
  data::DataListener<rec::audio::source::StereoProto>::startListening();
  data::DataListener<rec::audio::stretch::Stretch>::startListening();
  playbackSpeed_.startListening();
  pitchScale_.startListening();
  fineScale_.startListening();
  enableButton_.startListening();
}

void TransformController::operator()(const Stretch& s) {
  MessageManagerLock l;
  playbackSpeed_.setEnabled(s.enabled());
  pitchScale_.setEnabled(s.enabled());
  fineScale_.setEnabled(s.enabled());
  stereoComboBox_.setEnabled(s.enabled());
}

void TransformController::operator()(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  MessageManagerLock l;
  stereoComboBox_.setSelectedId(sides, true);
}

void TransformController::comboBoxChanged(juce::ComboBox* box) {
  if (box == &stereoComboBox_) {
    Sides sides = static_cast<Sides>(stereoComboBox_.getSelectedId());
    StereoProto stereo;
    if (sides != STEREO) {
      stereo.set_type(StereoProto::SINGLE);
      stereo.set_side(static_cast<StereoProto::Side>(sides - 2));
    }
    DataListener<StereoProto>::setProto(stereo);
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

