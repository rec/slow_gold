#include "rec/command/map/MidiEditor.h"

#include "rec/audio/Device.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/MidiName.h"
#include "rec/util/thread/CallAsync.h"

TRAN(WAITING, "Waiting for a MIDI note, program change or controller...");
TRAN(MIDI, "MIDI");

namespace rec {
namespace command {

namespace {

string toString(const MidiMessage& msg) {
    string r = midiToString(msg);
    if (msg.isNoteOn())
        r[2] = 127;

    if (msg.isController())
        r[2] = (r[2] < 64) ? 0 : 127;

    return r;
}

}  // namespace

const String MidiEditor::name() const {
    return t_MIDI;
}

const String MidiEditor::getDescription(const string& key) const {
    return midiName(midiFromString(key));
}

void MidiEditor::operator()(const MidiMessage& m) {
    if (entryWindow_ &&
            (m.isNoteOn() || m.isProgramChange() || m.isController())) {
        setKey(toString(m));
    }
}

const String MidiEditor::getWindowTitle() const {
    return t_WAITING;
}

}  // namespace command
}  // namespace rec
