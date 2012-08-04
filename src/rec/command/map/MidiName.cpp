#include "rec/command/map/MidiName.h"
#include "rec/base/Trans.h"

namespace rec {
namespace command {

namespace {

String midiNoteName(const MidiMessage& msg) {
  return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3);
}

TRTR(AS, "as");
TRTR(SYSEX, "sysex");
TRTR(NOTE_OFF, "%s off");
TRTR(PC, "pc %d");

}  // namespace

String midiName(const MidiMessage& m) {
  if (m.isActiveSense())
    return AS;

  if (m.isSysEx())
    return SYSEX;

  if (m.isNoteOn())
    return midiNoteName(m);

  if (m.isNoteOff())
    return String::formatted(NOTE_OFF, c_str(midiNoteName(m)));

  if (m.isProgramChange())
    return String::formatted(PC, m.getProgramChangeNumber());

  if (m.isController()) {
    return MidiMessage::getControllerName(m.getControllerNumber()) +
      String(m.getControllerValue());
  }

  return "?";
}

void MidiName::registerAllTranslations() {
  AS.registerTranslation();
  SYSEX.registerTranslation();
  NOTE_OFF.registerTranslation();
  PC.registerTranslation();
}

}  // namespace command
}  // namespace rec

