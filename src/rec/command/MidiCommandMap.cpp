#include "rec/command/MidiCommandMap.h"

namespace rec {
namespace command {

MidiCommandMap::MidiCommandMap(ApplicationCommandManager* m)
    : manager_(m), listener_(NULL), enable_(true) {
}

void MidiCommandMap::handleIncomingMidiMessage(juce::MidiInput*,
                                               const juce::MidiMessage& msg) {
  {
    ScopedLock l(lock_);
    if (listener_) {
      (*listener_)(msg);
      listener_ = NULL;
      return;
    }

    if (!enable_)
      return;
  }

  invoke(str(msg), manager_);
}

void MidiCommandMap::requestOneMessage(Listener<const juce::MidiMessage&>* lt) {
  ScopedLock l(lock_);
  listener_ = lt;
}

void MidiCommandMap::setEnable(bool e) {
  ScopedLock l(lock_);
  enable_ = e;
}

}  // namespace command
}  // namespace rec
