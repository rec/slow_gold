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
    : Panel("TransformController", HORIZONTAL),

      playbackSpeed_("Stretch", "Playback Speed Slider: "
                     "Controls how fast the loop plays back: "
                     "higher numbers mean the loop plays back faster.",
                     getTypeName<Stretch>(), "time_percent"),

      pitchScale_("Pitch", "Playback Tuning Slider: "
                  "Coarse loop playback up and down in pitch, "
                  "measured in semitones.",
                  getTypeName<Stretch>(), "semitone_shift"),

      fineScale_("Tune", "Playback Fine Tuning Slider: "
                 "Fine tune loop up or down in pitch, measured in "
                 "cents (1/100 of a semitone).",
                 getTypeName<Stretch>(), "detune_cents"),

      masterTune_("Master", "Master Tune Slider: "
                  "Master tune is a global detune over all tracks.",
                  getTypeName<AudioSettings>(),
                  data::Address("master_tune") +
                  data::AddressProto::GLOBAL_SCOPE),

      enableButton_("Enable",       "Transform Enable Button: "
                    "Disable or enable all sound transformations: "
                    "pitch, time and stereo processing but not master tune.",
                    getTypeName<Stretch>(), "time_enabled"),

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
  // I don't understand why we need such a small radius.
  playbackSpeed_.slider()->setDetentRadius(0.008f);
  pitchScale_.slider()->setDetent(0.0f);
  fineScale_.slider()->setDetent(0.0f);
  masterTune_.slider()->setDetent(0.0f);

  playbackSpeed_.slider()->setTextValueSuffix("%");

  stereoComboBox_.setEditableText(false);
  stereoComboBox_.setJustificationType(Justification::centredLeft);
  stereoComboBox_.addListener(this);

  stereoComboBox_.addItem(Trans("Stereo"), STEREO);
  stereoComboBox_.addItem(Trans("Left"), LEFT);
  stereoComboBox_.addItem(Trans("Right"), RIGHT);
  stereoComboBox_.addItem(Trans("L + R"), LEFT_PLUS_RIGHT);

  leftPanel_.addToPanel(&enableButton_, ENABLE_BUTTON_HEIGHT);
  leftPanel_.addToPanel(&stereoComboBox_, COMBO_BOX_HEIGHT);
  leftPanel_.addToPanel(&leftPadding_);

  addToPanel(&leftPanel_, LEFT_PANEL_WIDTH);
  addToPanel(&rightPanel_, 150, -1.0, 250);
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

  stereoComboBox_.changeItemText(STEREO, Trans("Stereo"));
  stereoComboBox_.changeItemText(LEFT, Trans("Left"));
  stereoComboBox_.changeItemText(RIGHT, Trans("Right"));
  stereoComboBox_.changeItemText(LEFT_PLUS_RIGHT, Trans("L + R"));

  stereoComboBox_.setSelectedId(sides_, juce::dontSendNotification);
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

  stereoComboBox_.setSelectedId(sides_, juce::dontSendNotification);
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

