#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<KeyPressMappingSet> KeyCommandMapEditorBase;

class KeyCommandMapEditor : public KeyCommandMapEditorBase {
 public:
  typedef GenericCommandMapEditor<KeyPressMappingSet> Super;
  KeyCommandMapEditor(ApplicationCommandManager* acm, KeyPressMappingSet* mcm)
      : Super(acm, mcm) {
  }

  virtual const String name() const;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(KeyCommandMapEditor);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
