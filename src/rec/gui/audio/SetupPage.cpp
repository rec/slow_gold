#include "rec/gui/audio/SetupPage.h"

#include "rec/audio/Device.h"
#include "rec/base/Trans.h"
#include "rec/gui/Dialog.h"

namespace rec {
namespace gui {
namespace audio {

static Trans SET_AUDIO_PREFERENCES("Set Audio Preferences");

SetupPage::SetupPage(rec::audio::Device* dev)
    : deviceSelector_(dev->manager_, 0, 0, 2, 2, true, false, true, true),
      device_(dev) {
  addAndMakeVisible(&deviceSelector_);
  setSize(400, 300);
}

void SetupPage::paint(Graphics& g) { g.fillAll(juce::Colours::lightgrey); }

void SetupPage::resized() {
  deviceSelector_.setBounds(8, 8, getWidth() - 16, getHeight() - 16);
}

void SetupPage::show(Component* comp) {
  DialogLocker locker;
  if (!locker.isLocked())
    return;

  locker.setModalComponent(comp);
  juce::DialogWindow::showModalDialog(SET_AUDIO_PREFERENCES, this,
                                      comp, juce::Colours::white, true);

  device_->saveState();
  device_->setSamplesPerSecondFromDevice();
}

void SetupPage::translateAll() {
  SET_AUDIO_PREFERENCES.translate();
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
