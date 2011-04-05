#ifndef __REC_GUI_AUDIOSETUPPAGE__
#define __REC_GUI_AUDIOSETUPPAGE__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class AudioSetupPage  : public Component {
 public:
  explicit AudioSetupPage(AudioDeviceManager& adm)
      : deviceSelector_(adm, 0, 0, 2, 2, false, false, true, true) {
    addAndMakeVisible(&deviceSelector_);
    setSize(400, 300);
  }

  void paint(Graphics& g) { g.fillAll (Colours::lightgrey); }

  void resized() {
    deviceSelector_.setBounds(8, 8, getWidth() - 16, getHeight() - 16);
  }

 private:
  AudioDeviceSelectorComponent deviceSelector_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AudioSetupPage);
};

}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_AUDIOSETUPPAGE__
