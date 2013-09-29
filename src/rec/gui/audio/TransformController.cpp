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
      enableButton_("Enable", "Transform Enable Button: "
                    "Disable or enable all sound transformations: "
                    "pitch, time and stereo processing but not master tune.",
                    makeAddress<Stretch>("time_enabled")),
      leftPanel_("Left", VERTICAL),
      rightPanel_(gui::makeLayout("RightTransformPanel", this)) {
  if (not USE_NEW_GUI) {
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
  } else {
    newLeftPanel_ = gui::makeLayout("LeftTransformPanel", this);
    addToPanel(newLeftPanel_.get(), LEFT_PANEL_WIDTH);
  }

  addToPanel(rightPanel_.get(), 150, -1.0, 250);
}

TransformController::~TransformController() {}

void TransformController::operator()(const Stretch& s) {
  setStretch(s);
}

void TransformController::languageChanged() {
  if (USE_NEW_GUI)
    return;
  stereoComboBox_.setTooltip(
      Trans("Stereo Processing Menu:  Choose between the "
            "original stereo, just the left channel, "
            "just the right channel, "
            "or a mono mix of both channels."));

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

