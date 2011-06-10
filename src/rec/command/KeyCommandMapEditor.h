#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/GenericCommandMapEditor.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<KeyPressMappingSet, KeyPress> KeyCommandMapEditor;

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
