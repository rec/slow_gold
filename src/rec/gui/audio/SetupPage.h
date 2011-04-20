#ifndef __REC_GUI_AUDIO_SETUPPAGE__
#define __REC_GUI_AUDIO_SETUPPAGE__

#include "rec/base/base.h"

namespace rec {
namespace gui {
namespace audio {

class SetupPage  : public Component {
 public:
  explicit SetupPage(AudioDeviceManager* manager)
      : deviceSelector_(*manager, 0, 0, 2, 2, false, false, true, true) {
    addAndMakeVisible(&deviceSelector_);
    setSize(400, 300);
  }

  void paint(Graphics& g) { g.fillAll(juce::Colours::lightgrey); }

  void resized() {
    deviceSelector_.setBounds(8, 8, getWidth() - 16, getHeight() - 16);
  }

  void show(Component* comp) {
    juce::DialogWindow::showModalDialog("Set Audio Preferences", this, comp,
                                        juce::Colours::white, true);
  }

 private:
  juce::AudioDeviceSelectorComponent deviceSelector_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetupPage);
};


}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif   // __REC_GUI_AUDIO_SETUPPAGE__
