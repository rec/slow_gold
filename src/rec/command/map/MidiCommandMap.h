#ifndef __REC_COMMAND_MIDICOMMANDMAP__
#define __REC_COMMAND_MIDICOMMANDMAP__

#include "rec/command/map/CommandMap.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

class MidiCommandMap : public CommandMap,
                       public juce::MidiInputCallback,
                       public ChangeBroadcaster {
 public:
  MidiCommandMap(ApplicationCommandManager* m);
  virtual void handleIncomingMidiMessage(juce::MidiInput*,
                                         const juce::MidiMessage&);
  void requestOneMessage(Listener<const juce::MidiMessage&>* lst);
  void setEnable(bool e);
  virtual void changeListenerCallback(ChangeBroadcaster*) {}

 private:
  CriticalSection lock_;
  ApplicationCommandManager* const manager_;
  Listener<const juce::MidiMessage&>* listener_;
  bool enable_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiCommandMap);
};

const string toBytes(const MidiMessage&);
const string toBytes(const KeyBase&);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAP__
