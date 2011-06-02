#ifndef __REC_COMMAND_MIDICOMMANDMAP__
#define __REC_COMMAND_MIDICOMMANDMAP__

#include "rec/command/CommandMap.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace command {

class MidiCommandMap : public CommandMap, public juce::MidiInputCallback {
 public:
  MidiCommandMap(ApplicationCommandManager* m);
  virtual void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage&);
  void requestOneMessage(Listener<const juce::MidiMessage&>* lst);
  void setEnable(bool e);

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
