#if 0

#include "rec/audio/util/AudioDeviceSetup.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/persist/Persist.h"

using namespace juce;
//using namespace rec::audio;

// using rec::audio::AudioDeviceSetupProto;

namespace rec {
namespace persist {

AudioDeviceSetupListener::AudioDeviceSetupListener(AudioDeviceManager* manager)
    : manager_(manager) {
  AudioDeviceSetup setup;
  bool readSuccessful = false;
  AudioDeviceSetupProto proto = get<AudioDeviceSetupProto>();
  if (!proto.output_device_name().size()) {
    VLOG(1) << "Using default audio setup";

  } else if (!copy(proto, &setup)) {
    LOG(ERROR) << "Couldn't copy audio setup data";

  } else {
    String err = manager->setAudioDeviceSetup(setup, true);
    readSuccessful = (err.length() == 0);
    if (!readSuccessful)
      LOG(ERROR) << "Couldn't setAudioDeviceSetup, error " << err;
  }

  if (!readSuccessful)
    manager->initialise(0, 2, 0, true, String::empty, 0);

  manager->addChangeListener(this);
}

AudioDeviceSetupListener::~AudioDeviceSetupListener() {
  manager_->removeChangeListener(this);
}

void AudioDeviceSetupListener::changeListenerCallback(ChangeBroadcaster* cb) {
  audio::AudioDeviceSetupProto setupProto;
  if (copy(*manager_, &setupProto)) {
    persist::set(setupProto);
    LOG(INFO) << "Audio setup changed";
  } else {
    LOG(ERROR) << "Unable to copy AudioDeviceSetupProto";
  }
}

}  // namespace persist
}  // namespace rec
#endif