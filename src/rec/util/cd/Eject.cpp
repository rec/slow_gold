#include "rec/util/cd/Eject.h"

namespace rec {
namespace util {
namespace cd {

using juce::AudioCDBurner;

void ejectAll() {
  StringArray burners = AudioCDBurner::findAvailableDevices();
  for (int i = 0; i < burners.size(); ++i) {
    ptr<AudioCDBurner>(AudioCDBurner::openDevice(i))->openTray();
    DLOG(INFO) << "Burner " << burners[i];
  }
}

}  // namespace cd
}  // namespace util
}  // namespace rec
