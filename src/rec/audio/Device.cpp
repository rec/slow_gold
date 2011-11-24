#include "rec/audio/Device.h"
#include "rec/app/Files.h"

namespace rec {
namespace audio {

static File getDeviceFile() {
  return app::getAppFile("AudioDevice.xml");
}

Device::Device() {
  loadState();
  setupPage_.reset(new SetupPage(this));
}

void Device::loadState() {
  ptr<juce::XmlElement> state;

  File f = getDeviceFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));

  String err = manager_.initialise(0, 2, state.get(), true);
  if (err.length())
    LOG(DFATAL) << "Couldn't initialize audio::Device, error " << str(err);
}

void Device::saveState() {
  ptr<juce::XmlElement> state(manager_.createStateXml());
  if (state) {
    if (!state->writeToFile(getDeviceFile(), ""))
      LOG(DFATAL) << "Couldn't write device state file";
  }
}

}  // namespace audio
}  // namespace rec
