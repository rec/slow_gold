#pragma once

#include "rec/base/base.h"

namespace rec {
namespace command {

const string midiToString(const MidiMessage&);
String midiName(const MidiMessage& msg);

}  // namespace command
}  // namespace rec
