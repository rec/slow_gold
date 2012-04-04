#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {

static String midiNoteName(const MidiMessage& msg) {
  return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3);
}

// TRANS

String midiName(const MidiMessage& m) {
  if (m.isActiveSense())
    return trans("as");

  if (m.isSysEx())
    return trans("sysex");

  if (m.isNoteOn())
    return midiNoteName(m);

  if (m.isNoteOff())
    return String::formatted(trans("%s off"), c_str(midiNoteName(m)));

  if (m.isProgramChange())
    return String::formatted(trans("pc %d"), m.getProgramChangeNumber());

  if (m.isController()) {
    return MidiMessage::getControllerName(m.getControllerNumber()) +
      String(m.getControllerValue());
  }

  return "?";
}

}  // namespace command
}  // namespace rec

