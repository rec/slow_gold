#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {

static String midiNoteName(const MidiMessage& msg) {
  return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3);
}

String midiName(const MidiMessage& m) {
  if (m.isActiveSense())
    return "as";

  if (m.isSysEx())
    return "sysex";

  if (m.isNoteOn())
    return midiNoteName(m);

  if (m.isNoteOff())
    return midiNoteName(m) + " off";

  if (m.isProgramChange())
    return "pc " + String(m.getProgramChangeNumber());

  if (m.isController()) {
    return MidiMessage::getControllerName(m.getControllerNumber()) +
      String(m.getControllerValue());
  }

  return "?";
}

}  // namespace command
}  // namespace rec

