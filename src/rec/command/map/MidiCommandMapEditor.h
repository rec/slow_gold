#ifndef __REC_COMMAND_MIDICOMMANDMAPEDITOR__
#define __REC_COMMAND_MIDICOMMANDMAPEDITOR__

#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

typedef GenericCommandMapEditor<MidiCommandMap> MidiCommandMapEditorBase;

class MidiCommandMapEditor : public MidiCommandMapEditorBase {
 public:
  typedef GenericCommandMapEditor<MidiCommandMap> Super;
  MidiCommandMapEditor(ApplicationCommandManager* acm, MidiCommandMap* mcm)
      : Super(acm, mcm) {
  }

  virtual const String name() const;
  virtual bool isValid(const string&) const { return true; }
  virtual const String getDescription(const string&) const;
  virtual CommandID getCommand(const string&);

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiCommandMapEditor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAPEDITOR__
