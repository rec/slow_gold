#pragma once

#include "rec/gui/audio/SetupPage.h"
#include "rec/base/SampleRate.h"

namespace rec {
namespace audio {

class Device : public juce::ChangeListener {
 public:
  typedef gui::audio::SetupPage SetupPage;

  Device();

  mutable AudioDeviceManager manager_;
  ptr<SetupPage> setupPage_;

  void saveState();
  void shutdown();

  virtual void changeListenerCallback(ChangeBroadcaster*);
  SampleRate getSampleRate() const;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Device)
};

}  // namespace audio
}  // namespace rec

