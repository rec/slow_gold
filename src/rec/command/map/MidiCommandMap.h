#pragma once

#include "rec/command/map/CommandMap.h"

namespace rec {
namespace command {

class MidiCommandMap : public CommandMap,
                                              public juce::MidiInputCallback {
  public:
    MidiCommandMap();
    virtual void handleIncomingMidiMessage(juce::MidiInput*, const MidiMessage&);
    void requestOneMessage(Listener<const MidiMessage&>* lst);

  private:
    CriticalSection lock_;
    Listener<const juce::MidiMessage&>* listener_;
    bool enable_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(MidiCommandMap);
};

}  // namespace command
}  // namespace rec
