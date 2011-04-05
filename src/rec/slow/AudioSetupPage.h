#ifndef __JUCER_HEADER_AUDIODEMOSETUPPAGE_AUDIODEMOSETUPPAGE_244CE6A7__
#define __JUCER_HEADER_AUDIODEMOSETUPPAGE_AUDIODEMOSETUPPAGE_244CE6A7__

#include "rec/base/base.h"

namespace rec {
namespace slow {

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

}  // namespace rec
}  // namespace slow

#endif   // __JUCER_HEADER_AUDIODEMOSETUPPAGE_AUDIODEMOSETUPPAGE_244CE6A7__
