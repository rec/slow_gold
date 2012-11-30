#include "rec/command/map/MidiCommandMap.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/FunctionCallback.h"

#define FAKE_MIDI

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

#ifdef FAKE_MIDI
static void fakeMidi(MidiCommandMap* mcm) {
  Thread::sleep(2000);
  mcm->handleIncomingMidiMessage(NULL, MidiMessage(1, 10, 64));
}
#endif

void MidiCommandMap::requestOneMessage(Listener<const juce::MidiMessage&>* lt) {
  Lock l(lock_);
  listener_ = lt;
#ifdef FAKE_MIDI
  thread::runInNewThread("midi", 5, thread::functionCB(&fakeMidi, this));
#endif
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
