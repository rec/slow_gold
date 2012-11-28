#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<KeyPressMappingSet, KeyBase> KeyCommandMapEditor;

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
