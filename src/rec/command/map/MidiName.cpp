#include "rec/command/map/MidiName.h"
#include "rec/base/Trans.h"

TRAN(AS, "as");
TRAN(SYSEX, "sysex");
TRAN(NOTE_OFF, "%s off");
TRAN(PC, "pc %d");

namespace rec {
namespace command {

namespace {

String midiNoteName(const MidiMessage& msg) {
    return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3);
}

}  // namespace

const string midiToString(const MidiMessage& msg) {
    auto size = msg.getRawDataSize();
    auto data = msg.getRawData();
    string s(size + 1, 0);
    for (auto i = 0; i < size; ++i)
        s[i] = static_cast<char>(data[i]);

    return s;
    // return string(reinterpret_cast<const char*>(msg.getRawData()), size);
}

String midiName(const MidiMessage& m) {
    if (m.isActiveSense())
        return t_AS;

    if (m.isSysEx())
        return t_SYSEX;

    if (m.isNoteOn())
        return midiNoteName(m);

    if (m.isNoteOff())
        return String::formatted(t_NOTE_OFF, c_str(midiNoteName(m)));

    if (m.isProgramChange())
        return String::formatted(t_PC, m.getProgramChangeNumber());

    if (m.isController()) {
        return MidiMessage::getControllerName(m.getControllerNumber()) +
            String(m.getControllerValue());
    }

    return "?";
}

}  // namespace command
}  // namespace rec
