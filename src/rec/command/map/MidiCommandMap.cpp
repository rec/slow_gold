#include "rec/command/map/MidiCommandMap.h"
#include "rec/command/map/MidiName.h"
#include "rec/program/JuceModel.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/FunctionCallback.h"

// #define FAKE_MIDI

namespace rec {
namespace command {

MidiCommandMap::MidiCommandMap()
    : listener_(nullptr), enable_(true) {
}

void MidiCommandMap::handleIncomingMidiMessage(juce::MidiInput*,
                                               const juce::MidiMessage& msg) {
  Listener<const juce::MidiMessage&>* listener;
  {
    Lock l(lock_);
    listener = listener_;
    listener_ = nullptr;
  }

  if (listener)
    (*listener)(msg);
  else
    invokeAsync(midiToString(msg), program::applicationCommandManager());
}

#ifdef FAKE_MIDI
static void fakeMidi(MidiCommandMap* mcm) {
  Thread::sleep(2000);
  mcm->handleIncomingMidiMessage(nullptr,
                                 MidiMessage::noteOn(1, 10,
                                                     static_cast<uint8>(64)));
}
#endif

void MidiCommandMap::requestOneMessage(Listener<const juce::MidiMessage&>* lt) {
  Lock l(lock_);
  listener_ = lt;
#ifdef FAKE_MIDI
  thread::runInNewThread("midi", 5, thread::functionCB(&fakeMidi, this));
#endif
}

}  // namespace command
}  // namespace rec
