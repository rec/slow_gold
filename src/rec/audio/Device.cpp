#include "rec/audio/Device.h"
#include "rec/app/Files.h"
#include "rec/base/SampleTime.h"


namespace rec {
namespace audio {

static File getDeviceFile() {
  return app::getAppFile("AudioDevice.xml");
}

Device::Device() {
  ptr<juce::XmlElement> state;

  File f = getDeviceFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));

  String err = manager_.initialise(0, 2, state.get(), true);
  if (err.length())
    LOG(DFATAL) << "Couldn't initialize audio::Device, error " << str(err);
  setupPage_.reset(new SetupPage(this));

  setSampleRateFromDevice();
}

void Device::saveState() {
  ptr<juce::XmlElement> state(manager_.createStateXml());
  if (state) {
    if (!state->writeToFile(getDeviceFile(), ""))
      LOG(DFATAL) << "Couldn't write device state file";
  }
}

void Device::shutdown() {
  manager_.closeAudioDevice();
}

void Device::setSampleRateFromDevice() {
  AudioDeviceManager::AudioDeviceSetup setup;
  manager_.getAudioDeviceSetup(setup);
  SampleTime rate = static_cast<int64>(setup.sampleRate);
  if (!rate) {
    // TODO: default rate?  see
    // http://www.rawmaterialsoftware.com/viewtopic.php?f=2&t=9359
    LOG(ERROR) << "Zero sampleRate: using default";
    rate = 44100;
  }

  SampleTime::setSampleRate(rate);
}

}  // namespace audio
}  // namespace rec
