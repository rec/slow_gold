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

const int SLIDER_HEIGHT = 30;
const int FINE_OFFSET = 7;
const int LEFT_PANEL_WIDTH = 67;
const int ENABLE_BUTTON_HEIGHT = 30;
const int COMBO_BOX_HEIGHT = 30;

}  // namespace

using rec::audio::stretch::Stretch;

TransformController::TransformController()
    : Layout("TransformController", HORIZONTAL),
      playbackSpeed_("Stretch", getTypeName<Stretch>(), "time_percent"),
      pitchScale_("Pitch", getTypeName<Stretch>(), "semitone_shift"),
      fineScale_("Tune", getTypeName<Stretch>(), "detune_cents"),
      masterTune_("Master", getTypeName<AudioSettings>(), "master_tune",
                  GLOBAL_SCOPE),
      enableButton_("Enable", getTypeName<Stretch>(), "time_enabled"),
      leftPanel_("Left", VERTICAL),
      rightPanel_("Right", VERTICAL),
      showMasterTune_(true),
      rightPanelCreated_(false),
      sides_(STEREO) {
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

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.addListener(this);

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

void TransformController::languageChanged() {
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

  pitchScale_.slider()->setTextValueSuffix(String(" ") + Trans("semitones"));
  fineScale_.slider()->setTextValueSuffix(String(" ") + Trans("cents"));
  masterTune_.slider()->setTextValueSuffix(String(" ") + Trans("cents"));

  stereoComboBox_.clear();
  stereoComboBox_.setTextWhenNothingSelected(Trans("Stereo"));
  stereoComboBox_.setTextWhenNoChoicesAvailable(Trans("Stereo"));
  stereoComboBox_.addItem(Trans("Stereo"), STEREO);
  stereoComboBox_.addItem(Trans("Left"), LEFT);
  stereoComboBox_.addItem(Trans("Right"), RIGHT);
  stereoComboBox_.addItem(Trans("L + R"), LEFT_PLUS_RIGHT);
  stereoComboBox_.setSelectedId(sides_, true);
}

void TransformController::setStretch(const Stretch& s) {
#ifdef USE_STRETCH_ENABLE
  bool enabled = s.enabled();
#else
  bool enabled = true;
#endif
  playbackSpeed_.setEnabled(enabled && s.time_enabled());
  pitchScale_.setEnabled(enabled && s.pitch_enabled());
  fineScale_.setEnabled(enabled && s.pitch_enabled());
  stereoComboBox_.setEnabled(enabled);
}

void TransformController::operator()(const StereoProto& stereo) {
  sides_ = STEREO;
  if (stereo.type())
    sides_ = static_cast<Sides>(2 + stereo.side());

  stereoComboBox_.setSelectedId(sides_, true);
}

void TransformController::comboBoxChanged(juce::ComboBox* box) {
  if (box == &stereoComboBox_) {
    if (int id = stereoComboBox_.getSelectedId()) {
      Sides sides = static_cast<Sides>(id);
      StereoProto stereo;
      if (sides != STEREO) {
        stereo.set_type(StereoProto::SINGLE);
        stereo.set_side(static_cast<StereoProto::Side>(sides - 2));
      }
      DataListener<StereoProto>::setProto(stereo);
    }
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

