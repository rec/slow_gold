#pragma once

#include "rec/gui/audio/SetupPage.h"
#include "rec/base/SampleRate.h"

namespace rec {
namespace audio {

class Device : public juce::ChangeListener {
  public:
    using SetupPage = gui::audio::SetupPage;

    Device();

    mutable AudioDeviceManager manager_;
    std::unique_ptr<SetupPage> setupPage_;

    void saveState();
    void shutdown();

    virtual void changeListenerCallback(ChangeBroadcaster*);
    SampleRate getSampleRate() const;

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(Device)
};

}  // namespace audio
}  // namespace rec
