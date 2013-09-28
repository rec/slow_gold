#include "rec/gui/audio/TransformController.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/source/Stereo.h"
#include "rec/gui/proto/Layout.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::data;

namespace rec {
namespace gui {
namespace audio {

// Skin

using rec::audio::Gain;
using rec::audio::AudioSettings;

namespace {

const int SLIDER_HEIGHT = 30;
const int FINE_OFFSET = 7;
const int LEFT_PANEL_WIDTH = 67;
const int ENABLE_BUTTON_HEIGHT = 30;
const int COMBO_BOX_HEIGHT = 30;

}  // namespace

using rec::audio::stretch::Stretch;

bool USE_NEW_GUI = not not true;

TransformController::TransformController()
    : Panel("TransformController", HORIZONTAL),

      playbackSpeed_("SpeedSlider", "Playback Speed Slider: "
                     "Controls how fast the loop plays back: "
                     "higher numbers mean the loop plays back faster.",
                     "Speed", makeAddress<Stretch>("time_percent")),

      pitchScale_("PitchSlider", "Playback Tuning Slider: "
                  "Coarse loop playback up and down in pitch, "
                  "measured in semitones.",
                  "Pitch", makeAddress<Stretch>("semitone_shift")),

      fineScale_("TuneSlider", "Playback Fine Tuning Slider: "
                 "Fine tune loop up or down in pitch, measured in "
                 "cents (1/100 of a semitone).",
                 "Tune", makeAddress<Stretch>("detune_cents")),

      masterTune_("MasterTuneSlider", "Master Tune Slider: "
                  "Master tune is a global detune over all tracks.",
                  "Master Tune", makeAddress<AudioSettings>("master_tune")),

      enableButton_("Enable", "Transform Enable Button: "
                    "Disable or enable all sound transformations: "
                    "pitch, time and stereo processing but not master tune.",
                    makeAddress<Stretch>("time_enabled")),

      leftPanel_("Left", VERTICAL),
      rightPanel_("Right", VERTICAL),
      showMasterTune_(true),
      rightPanelCreated_(false) {
  playbackSpeed_.slider()->setRange(5.0, 200.0, 0.1);
  pitchScale_.slider()->setRange(-24.0, 24.0, 1.0);
  fineScale_.slider()->setRange(-50.0, 50.0, 0.1);
  masterTune_.slider()->setRange(-100.0, 100.0, 0.1);

  playbackSpeed_.slider()->setDetent(100.0f);
  // I don't understand why we need such a small radius.
  playbackSpeed_.slider()->setDetentRadius(0.008f);
  pitchScale_.slider()->setDetent(0.0f);
  fineScale_.slider()->setDetent(0.0f);
  masterTune_.slider()->setDetent(0.0f);

  playbackSpeed_.slider()->setTextValueSuffix("%");

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.addListener(this);

  stereoComboBox_.addItem(Trans("Stereo"), 1);
  stereoComboBox_.addItem(Trans("Left"), 2);
  stereoComboBox_.addItem(Trans("Right"), 3);
  stereoComboBox_.addItem(Trans("L + R"), 4);

  leftPanel_.addToPanel(&enableButton_, ENABLE_BUTTON_HEIGHT);
  leftPanel_.addToPanel(&stereoComboBox_, COMBO_BOX_HEIGHT);
  leftPanel_.addToPanel(&leftPadding_);

  addToPanel(&leftPanel_, LEFT_PANEL_WIDTH);
  if (USE_NEW_GUI) {
    newRightPanel_ = gui::makeLayout("RightTransformPanel", this);
    addToPanel(newRightPanel_.get(), 150, -1.0, 250);
  } else {
    addToPanel(&rightPanel_, 150, -1.0, 250);
  }
}

TransformController::~TransformController() {}

void TransformController::showMasterTune(bool show) {
  if (not USE_NEW_GUI and
      (!rightPanelCreated_ || showMasterTune_ != show)) {
    showMasterTune_ = show;
    if (rightPanelCreated_)
      rightPanel_.clear();
    else
      rightPanelCreated_ = true;

    int height = SLIDER_HEIGHT - (show ? FINE_OFFSET : 0);
    rightPanel_.addToPanel(&playbackSpeed_, height);
    rightPanel_.addToPanel(&pitchScale_, height);
    rightPanel_.addToPanel(&fineScale_, height);

    if (show)
      rightPanel_.addToPanel(&masterTune_, height);
    rightPanel_.addToPanel(&rightPadding_);
    rightPanel_.layout();
  }
}

void TransformController::operator()(const Stretch& s) {
  setStretch(s);
}

void TransformController::languageChanged() {
  stereoComboBox_.setTooltip(
      Trans("Stereo Processing Menu:  Choose between the "
            "original stereo, just the left channel, "
            "just the right channel, "
            "or a mono mix of both channels."));

  pitchScale_.slider()->setTextValueSuffix(String(" ") + Trans("semitones"));
  fineScale_.slider()->setTextValueSuffix(String(" ") + Trans("cents"));
  masterTune_.slider()->setTextValueSuffix(String(" ") + Trans("cents"));

  stereoComboBox_.setTextWhenNothingSelected(Trans("Stereo"));
  stereoComboBox_.setTextWhenNoChoicesAvailable(Trans("Stereo"));

  stereoComboBox_.changeItemText(1, Trans("Stereo"));
  stereoComboBox_.changeItemText(2, Trans("Left"));
  stereoComboBox_.changeItemText(3, Trans("Right"));
  stereoComboBox_.changeItemText(4, Trans("L + R"));

  stereoComboBox_.setSelectedId(1, juce::dontSendNotification);
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
  stereo_ = stereo;
  rec::audio::source::fixStereo(&stereo_);
  stereoComboBox_.setSelectedId(stereo.value() + 1, juce::dontSendNotification);
}

void TransformController::comboBoxChanged(juce::ComboBox* box) {
  if (box == &stereoComboBox_) {
    if (int id = stereoComboBox_.getSelectedId()) {
      stereo_.set_value(static_cast<StereoProto::Value>(id - 1));
      DataListener<StereoProto>::setProto(stereo_);
    }
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

