#include "rec/command/map/MidiCommandMap.h"

namespace rec {
namespace command {

MidiCommandMap::MidiCommandMap(ApplicationCommandManager* m)
    : manager_(m), listener_(NULL), enable_(true) {
}

void MidiCommandMap::handleIncomingMidiMessage(juce::MidiInput*,
                                               const juce::MidiMessage& msg) {
  Listener<const juce::MidiMessage&>* listener;
  {
    Lock l(lock_);
    listener = listener_;
    listener_ = NULL;
  }

  if (listener)
    (*listener)(msg);
  else
    invokeAsync(toBytes(msg), manager_);
}

void MidiCommandMap::requestOneMessage(Listener<const juce::MidiMessage&>* lt) {
  Lock l(lock_);
  listener_ = lt;
}

void MidiCommandMap::setEnable(bool e) {
  Lock l(lock_);
  enable_ = e;
}

const string toBytes(const MidiMessage& msg) {
  string r = str(msg);
  if (msg.isNoteOn())
    r[2] = 127;

  if (msg.isController())
    r[2] = (r[2] < 64) ? 0 : 127;

  return r;
}

const string toBytes(const KeyBase& key) {
  const Key<MidiMessage>* mm = dynamic_cast<const Key<MidiMessage>*>(&key);
  string result;
  if (mm)
    result = toBytes(*mm);
  else
    LOG(DFATAL) << "Couldn't convert KeyBase to Midi bytes";
  return result;
}

}  // namespace command
}  // namespace rec
