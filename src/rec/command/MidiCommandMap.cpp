#include "rec/command/MidiCommandMap.h"

namespace rec {
namespace command {

MidiCommandMap::MidiCommandMap(ApplicationCommandManager* m)
    : manager_(m), listener_(NULL), enable_(true) {
}

void MidiCommandMap::handleIncomingMidiMessage(juce::MidiInput*,
                                               const juce::MidiMessage& msg) {
  Listener<const juce::MidiMessage&>* listener;
  {
    ScopedLock l(lock_);
    listener = listener_;
    listener_ = NULL;

    if (!(enable_ || listener))
      return;
  }

  if (listener)
    (*listener)(msg);
  else
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
