#include "rec/gui/audio/TransformController.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

namespace rec {
namespace gui {
namespace audio {

// Skin

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

}  // namespace

using rec::audio::stretch::Stretch;

TransformController::TransformController()
    : Layout("TransformController", HORIZONTAL),
      playbackSpeed_(Trans("Speed"), getTypeName<Stretch>(),
                     Address("time_percent")),
      pitchScale_(Trans("Pitch"), getTypeName<Stretch>(),
                  Address("semitone_shift")),
      fineScale_(Trans("Tune"), getTypeName<Stretch>(),
                 Address("detune_cents")),
      enableButton_(Trans("Transform"), getTypeName<Stretch>(),
                    Address("enabled")),
      leftPanel_("Left", VERTICAL),
      rightPanel_("Right", VERTICAL) {
  playbackSpeed_.slider()->setRange(5.0, 200.0, 0.1);
  pitchScale_.slider()->setRange(-24.0, 24.0, 1.0);
  fineScale_.slider()->setRange(-50.0, 50.0, 0.1);

  playbackSpeed_.slider()->setDetent(100.0f);
  playbackSpeed_.slider()->setDetentRadius(0.008f);  // TODO: Why so small?
  pitchScale_.slider()->setDetent(0.0f);
  fineScale_.slider()->setDetent(0.0f);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.setTextWhenNothingSelected(Trans("Stereo"));
  stereoComboBox_.setTextWhenNoChoicesAvailable(Trans("Stereo"));
  stereoComboBox_.addItem(Trans("Stereo"), STEREO);
  stereoComboBox_.addItem(Trans("Left"), LEFT);
  stereoComboBox_.addItem(Trans("Right"), RIGHT);
  stereoComboBox_.addItem(Trans("L + R"), LEFT_PLUS_RIGHT);
  stereoComboBox_.addListener(this);

  playbackSpeed_.setTooltip(
      Trans("Playback Speed Slider: "
            "Controls how fast the loop plays back: "
            "higher numbers mean the loop plays back faster."));
  pitchScale_.setTooltip(
      Trans("Playback Tuning Slider: "
            "Coarse loop playback up and down in pitch, "
            "measured in semitones."));
  fineScale_.setTooltip(
      Trans("Playback Fine Tuning Slider: "
            "Fine tune loop up or down in pitch, measured in "
            "cents (1/100 of a semitone)."));
  stereoComboBox_.setTooltip(
      Trans("Stereo Processing Menu:  choose between the "
            "original stereo, just the left channel, "
            "just the right channel, "
            "or a mono mix of both channels."));
  enableButton_.setTooltip(
      Trans("Transform Enable Button: "
            "Disable or enable all sound transformations: "
            "pitch, time and stereo processing."));

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
  thread::callAsync(this, &TransformController::setStretch, s);
}

void TransformController::setStretch(const Stretch& s) {
  playbackSpeed_.setEnabled(s.enabled());
  pitchScale_.setEnabled(s.enabled());
  fineScale_.setEnabled(s.enabled());
  stereoComboBox_.setEnabled(s.enabled());
}

void TransformController::operator()(const StereoProto& stereo) {
  Sides sides = STEREO;
  if (stereo.type())
    sides = static_cast<Sides>(2 + stereo.side());

  thread::callAsync(&stereoComboBox_, &juce::ComboBox::setSelectedId,
                    sides, true);
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

