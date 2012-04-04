#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/map/GenericCommandMapEditor.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<KeyPressMappingSet, juce::KeyPress> KeyCommandMapEditor;

struct KeyCommandMapEditorTranslator {
  static void translateAll();
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
