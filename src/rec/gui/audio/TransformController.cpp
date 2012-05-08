#include "rec/gui/audio/TransformController.h"

#include "rec/util/thread/CallAsync.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;

namespace rec {
namespace gui {
namespace audio {

// Skin

using rec::audio::Gain;
using rec::audio::AudioSettings;
using data::Address;

namespace {

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

const int SLIDER_HEIGHT = 30;
const int FINE_OFFSET = 7;
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
      masterTune_(Trans("Master"), getTypeName<AudioSettings>(),
                  Address("master_tune"), "", "", GLOBAL_SCOPE),
      enableButton_(Trans("Transform"), getTypeName<Stretch>(),
                    Address("enabled")),
      leftPanel_("Left", VERTICAL),
      rightPanel_("Right", VERTICAL),
      showMasterTune_(true),
      rightPanelCreated_(false) {
  playbackSpeed_.slider()->setRange(5.0, 200.0, 0.1);
  pitchScale_.slider()->setRange(-24.0, 24.0, 1.0);
  fineScale_.slider()->setRange(-50.0, 50.0, 0.1);
  masterTune_.slider()->setRange(-100.0, 100.0, 0.1);

  playbackSpeed_.slider()->setDetent(100.0f);
  playbackSpeed_.slider()->setDetentRadius(0.008f);  // TODO: Why so small?
  pitchScale_.slider()->setDetent(0.0f);
  fineScale_.slider()->setDetent(0.0f);
  masterTune_.slider()->setDetent(0.0f);

  playbackSpeed_.slider()->setTextValueSuffix("%");
  pitchScale_.slider()->setTextValueSuffix(" semitones");
  fineScale_.slider()->setTextValueSuffix(" cents");
  masterTune_.slider()->setTextValueSuffix(" cents");

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
      Trans("Stereo Processing Menu:  Choose between the "
            "original stereo, just the left channel, "
            "just the right channel, "
            "or a mono mix of both channels."));
  enableButton_.setTooltip(
      Trans("Transform Enable Button: "
            "Disable or enable all sound transformations: "
            "pitch, time and stereo processing but not master tunen."));

  masterTune_.setTooltip(
      Trans("Master Tune Slider: "
            "Master tune is a global detune over all tracks."));

  leftPanel_.addToLayout(&enableButton_, ENABLE_BUTTON_HEIGHT);
  leftPanel_.addToLayout(&stereoComboBox_, COMBO_BOX_HEIGHT);
  leftPanel_.addToLayout(&leftPadding_);

  addToLayout(&leftPanel_, LEFT_PANEL_WIDTH);
  addToLayout(&rightPanel_, 150, -1.0, 250);
}

TransformController::~TransformController() {}

void TransformController::showMasterTune(bool show) {
  if (!rightPanelCreated_ || showMasterTune_ != show) {
    showMasterTune_ = show;
    if (rightPanelCreated_)
      rightPanel_.clear();
    else
      rightPanelCreated_ = true;

    int height = SLIDER_HEIGHT - (show ? FINE_OFFSET : 0);
    rightPanel_.addToLayout(&playbackSpeed_, height);
    rightPanel_.addToLayout(&pitchScale_, height);
    rightPanel_.addToLayout(&fineScale_, height);

    if (show)
      rightPanel_.addToLayout(&masterTune_, height);
    rightPanel_.addToLayout(&rightPadding_);
    rightPanel_.layout();
  }
}

void TransformController::operator()(const Stretch& s) {
  setStretch(s);
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

