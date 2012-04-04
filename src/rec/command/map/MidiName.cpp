#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {

static String midiNoteName(const MidiMessage& msg) {
  return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3);
}

String midiName(const MidiMessage& m) {
  if (m.isActiveSense())
    return translate("as");

  if (m.isSysEx())
    return translate("sysex");

  if (m.isNoteOn())
    return midiNoteName(m);

  if (m.isNoteOff())
    return String::formatted(translate("%s off"), c_str(midiNoteName(m)));

  if (m.isProgramChange())
    return String::formatted(translate("pc %d"), m.getProgramChangeNumber());

  if (m.isController()) {
    return MidiMessage::getControllerName(m.getControllerNumber()) +
      String(m.getControllerValue());
  }

  return "?";
}

}  // namespace command
}  // namespace rec

