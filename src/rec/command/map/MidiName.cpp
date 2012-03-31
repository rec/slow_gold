#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {

// i18n

namespace {

const char* ACTIVE_SENSING = "as";
const char* SYSEX = "sysex";
const char* NOTE_OFF = "%s off";
const char* PROGRAM_CHANGE = "pc %d";

}

static String midiNoteName(const MidiMessage& msg) {
  return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3);
}

String midiName(const MidiMessage& m) {
  if (m.isActiveSense())
    return ACTIVE_SENSING;

  if (m.isSysEx())
    return SYSEX;

  if (m.isNoteOn())
    return midiNoteName(m);

  if (m.isNoteOff())
    return String::formatted(NOTE_OFF, c_str(midiNoteName(m)));

  if (m.isProgramChange())
    return String::formatted(PROGRAM_CHANGE, m.getProgramChangeNumber());

  if (m.isController()) {
    return MidiMessage::getControllerName(m.getControllerNumber()) +
      String(m.getControllerValue());
  }

  return "?";
}

}  // namespace command
}  // namespace rec

