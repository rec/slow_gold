#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/CommandMapEditor.h"
#include "rec/command/CommandMapEditButton.h"
#include "rec/command/CommandMapEditorMappingItem.h"
#include "rec/command/GenericCommandMapEditor.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<KeyPressMappingSet, KeyPress> KeyCommandMapEditor;

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
