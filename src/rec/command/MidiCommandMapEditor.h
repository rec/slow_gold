#ifndef __REC_COMMAND_MIDICOMMANDMAPEDITOR__
#define __REC_COMMAND_MIDICOMMANDMAPEDITOR__

#include "rec/command/GenericCommandMapEditor.h"
#include "rec/command/MidiCommandMap.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<MidiCommandMap, MidiMessage> MidiCommandMapEditor;

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAPEDITOR__
