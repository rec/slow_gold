#ifndef __REC_COMMAND_MIDICOMMANDMAPEDITOR__
#define __REC_COMMAND_MIDICOMMANDMAPEDITOR__

#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/command/map/MidiCommandMap.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<MidiCommandMap, MidiMessage> MidiCommandMapEditor;

struct MidiCommandMapEditorTranslator {
  static void translateAll();
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAPEDITOR__
