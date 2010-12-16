#include "rec/audio/AudioDeviceSetup.h"
#include "rec/slow/Preferences.h"
#include "rec/data/persist/Copy.h"

using namespace juce;
using namespace rec::audio;

namespace rec {
namespace persist {

bool copy(const AudioDeviceSetupProto& in, AudioDeviceSetup *out) {
  copy(in.output_device_name(), &out->outputDeviceName);
  copy(in.input_device_name(), &out->inputDeviceName);
  out->sampleRate = in.sample_rate();
  out->bufferSize = in.buffer_size();

  MemoryBlock block;
  copy(in.input_channels(), &block);
  out->inputChannels.loadFromMemoryBlock(block);

  out->useDefaultInputChannels = in.use_default_input_channels();
  copy(in.output_channels(), &block);
  out->outputChannels.loadFromMemoryBlock(block);
  out->useDefaultOutputChannels = in.use_default_output_channels();

  return true;
}

bool copy(const AudioDeviceSetup& in, AudioDeviceSetupProto* out) {
  copy(in.outputDeviceName, out->mutable_output_device_name());
  copy(in.inputDeviceName, out->mutable_input_device_name());
  out->set_sample_rate(in.sampleRate);
  out->set_buffer_size(in.bufferSize);
  MemoryBlock block = in.inputChannels.toMemoryBlock();
  copy(block, out->mutable_input_channels());
  out->set_use_default_input_channels(in.useDefaultInputChannels);

  block = in.outputChannels.toMemoryBlock();
  copy(block, out->mutable_output_channels());
  out->set_use_default_output_channels(in.useDefaultOutputChannels);

  return true;
}

bool copy(const AudioDeviceManager& in, audio::AudioDeviceSetup *out) {
  manager->getAudioDeviceSetup(setup);
  return true;
}

bool copy(const AudioDeviceManager& in, audio::AudioDeviceSetupProto *out) {
  AudioDeviceSetup setup;
  return copy(in, &setup) && copy(setup, out);
}

AudioDeviceSetupListener::AudioDeviceSetupListener(AudioDeviceManager* manager)
    : manager_(manager) {
  AudioDeviceSetup setup;
  if (audioSetupData()->fileReadSuccess()) {
    if (!persist::copy(slow::audioSetupData()->get(), &setup)) {
      LOG(ERROR) << "Couldn't copy audio setup data";
    } else {
      String err = deviceManager_->setAudioDeviceSetup(setup, true);
      if (err.length())
        LOG(ERROR) << "Couldn't setAudioDeviceSetup, error " << err;
      else
        DLOG(INFO) << "read audio setup from file";
    }
  }
  manager_->addListener(this);
}

AudioDeviceSetupListener::~AudioDeviceSetupListener() {
  manager_->removeListener(this);
}

void AudioDeviceSetupListener::changeListenerCallback(ChangeBroadcaster*) {
    audio::AudioDeviceSetupProto setupProto;
    if (copy(manager_, &setupProto)) {
      DLOG(INFO) << "Audio setup changed";
      slow::audioSetupData()->setter()->set(setupProto);
    } else {
      LOG(ERROR) << "Unable to copy AudioDeviceSetupProto";
    }
  }
}

}  // namespace persist
}  // namespace rec
