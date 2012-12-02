#include "rec/command/map/MidiEditor.h"

#include "rec/audio/Device.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/EntryWindow.h"
#include "rec/command/map/MidiName.h"
#include "rec/util/thread/CallAsync.h"

TRAN(WAITING, "Waiting for a MIDI note, program change or controller...");
TRAN(MIDI, "MIDI");

namespace rec {
namespace command {

const String MidiEditor::name() const {
  return t_MIDI;
}

const String MidiEditor::getDescription(const string& key) const {
  return midiName(midiFromString(key));
}

void MidiEditor::operator()(const MidiMessage& m) {
  if (commandEntryWindow() &&
      (m.isNoteOn() || m.isProgramChange() || m.isController())) {
    setKey(toString(m));
  }
}
EntryWindow* MidiEditor::newWindow() {
  return new EntryWindow(t_WAITING, this);
}


}  // namespace command
}  // namespace rec

