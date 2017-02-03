#include "rec/audio/Device.h"
#include "rec/audio/OutputSampleRate.h"
#include "rec/base/SampleRate.h"
#include "rec/app/Files.h"

namespace rec {
namespace audio {

static File getDeviceFile() {
  return app::getAppFile("global").getChildFile("AudioDevice.xml");
}

Device::Device() {
  manager_.addChangeListener(this);

  std::unique_ptr<juce::XmlElement> state;
  File f = getDeviceFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));
  else
    LOG(ERROR) << "Couldn't read device file " << str(f);

  String err = manager_.initialise(0, 2, state.get(), true);
  if (err.length())
    LOG(DFATAL) << "Couldn't initialize audio::Device, error " << str(err);

  setupPage_.reset(new SetupPage(this));
}

void Device::saveState() {
  std::unique_ptr<juce::XmlElement> state(manager_.createStateXml());
  if (state) {
    auto f = getDeviceFile();
    if (state->writeToFile(f, ""))
      LOG(INFO) << "Wrote state to file " << str(f);
    else
      LOG(DFATAL) << "Couldn't write device state file " << str(f);
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
