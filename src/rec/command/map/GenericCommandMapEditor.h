#ifndef __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
#define __REC_COMMAND_GENERICCOMMANDMAPEDITOR__

#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

template <typename MappingSet>
class GenericCommandMapEditor : public CommandMapEditor {
 public:
  GenericCommandMapEditor(ApplicationCommandManager*, MappingSet*);

 protected:
  MappingSet* mappings_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GenericCommandMapEditor);
};

template <typename MappingSet>
GenericCommandMapEditor<MappingSet>::
GenericCommandMapEditor(ApplicationCommandManager* manager, MappingSet* m)
    : CommandMapEditor(manager, m), mappings_(m) {
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
