#include "rec/audio/Device.h"
#include "rec/data/persist/AppDirectory.h"

namespace rec {
namespace audio {

namespace {

File getDeviceFile() {
  return getApplicationDirectory().getChildFile("AudioDevice.xml");
}

}

void Device::loadState() {
  ptr<juce::XmlElement> state;

  File f = getDeviceFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));

  String err = manager_.initialise(0, 2, state.get(), true);
  if (err.length())
    LOG(ERROR) << "Couldn't initialize audio::Device, error " << str(err);
}

void Device::saveState() {
  ptr<juce::XmlElement> state(manager_.createStateXml());
  if (state) {
    if (!state->writeToFile(getDeviceFile(), ""))
      LOG(ERROR) << "Couldn't write device statea file";
  }
}

}  // namespace audio
}  // namespace rec
