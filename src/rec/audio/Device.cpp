#include "rec/audio/Device.h"
#include "rec/audio/SampleRate.h"
#include "rec/app/Files.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace audio {

static File getDeviceFile() {
  return app::getAppFile("AudioDevice.xml");
}

Device::Device() {
  manager_.addChangeListener(this);

  ptr<juce::XmlElement> state;
  File f = getDeviceFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));

  String err = manager_.initialise(0, 2, state.get(), true);
  if (err.length())
    LOG(DFATAL) << "Couldn't initialize audio::Device, error " << str(err);

  setupPage_.reset(new SetupPage(this));
}

void Device::saveState() {
  ptr<juce::XmlElement> state(manager_.createStateXml());
  if (state) {
    if (!state->writeToFile(getDeviceFile(), ""))
      LOG(DFATAL) << "Couldn't write device state file";
  }
}

void Device::shutdown() {
  manager_.removeChangeListener(this);
  manager_.closeAudioDevice();
}

void Device::changeListenerCallback(ChangeBroadcaster*) {
  AudioDeviceManager::AudioDeviceSetup setup;
  manager_.getAudioDeviceSetup(setup);

  if (int rate = static_cast<int>(setup.sampleRate))
    setSampleRate(rate);
  else
    LOG(ERROR) << "Zero sampleRate";
}

}  // namespace audio
}  // namespace rec
