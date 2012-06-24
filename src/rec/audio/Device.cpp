#include "rec/audio/Device.h"
#include "rec/audio/OutputSampleRate.h"
#include "rec/base/SampleRate.h"
#include "rec/app/Files.h"

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

SampleRate Device::getSampleRate() const {
  AudioDeviceManager::AudioDeviceSetup setup;
  manager_.getAudioDeviceSetup(setup);
  return setup.sampleRate;
}

void Device::changeListenerCallback(ChangeBroadcaster*) {
  setOutputSampleRate(getSampleRate());
}

}  // namespace audio
}  // namespace rec
