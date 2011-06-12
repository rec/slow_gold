#ifndef __REC_COMMAND_MIDICOMMANDMAP__
#define __REC_COMMAND_MIDICOMMANDMAP__

#include "rec/command/CommandMap.h"

namespace rec {
namespace command {

class MidiCommandMap : public CommandMap,
                       public juce::MidiInputCallback,
                       public ChangeBroadcaster {
 public:
  MidiCommandMap(ApplicationCommandManager* m);
  virtual void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage&);
  void requestOneMessage(Listener<const juce::MidiMessage&>* lst);
  void setEnable(bool e);
  virtual void changeListenerCallback (ChangeBroadcaster*) {}
  const string toBytes(const MidiMessage& msg);

 private:
  CriticalSection lock_;
  ApplicationCommandManager* const manager_;
  Listener<const juce::MidiMessage&>* listener_;
  bool enable_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MidiCommandMap);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAP__
