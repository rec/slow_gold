#include "rec/gui/audio/SetupPage.h"
#include "rec/audio/Device.h"

namespace rec {
namespace gui {
namespace audio {

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
  juce::DialogWindow::showModalDialog("Set Audio Preferences", this, comp,
                                      juce::Colours::white, true);

  device_->saveState();
}


}  // namespace audio
}  // namespace gui
}  // namespace rec
