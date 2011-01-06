#ifndef __JUCER_HEADER_AUDIODEMOSETUPPAGE_AUDIODEMOSETUPPAGE_244CE6A7__
#define __JUCER_HEADER_AUDIODEMOSETUPPAGE_AUDIODEMOSETUPPAGE_244CE6A7__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class AudioSetupPage  : public Component {
 public:
  explicit AudioSetupPage(AudioDeviceManager& deviceManager)
      : deviceManager_(deviceManager) {
    deviceSelector_.reset(
        new AudioDeviceSelectorComponent(deviceManager_,
                                         0, 0, 2, 2, false, false, true, true));
    addAndMakeVisible(deviceSelector_.get());
    setSize(400, 200);
  }

  void paint(Graphics& g) { g.fillAll (Colours::lightgrey); }

  void resized() {
    deviceSelector_->setBounds(8, 8, getWidth() - 16, getHeight() - 16);
  }

 private:
  AudioDeviceManager& deviceManager_;
  ptr<AudioDeviceSelectorComponent> deviceSelector_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(AudioSetupPage);
};

}  // namespace rec
}  // namespace slow

#endif   // __JUCER_HEADER_AUDIODEMOSETUPPAGE_AUDIODEMOSETUPPAGE_244CE6A7__
