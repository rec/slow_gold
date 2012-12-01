#ifndef __REC_COMMAND_MIDICOMMANDMAPEDITOR__
#define __REC_COMMAND_MIDICOMMANDMAPEDITOR__

#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

class MidiCommandMapEditor : public CommandMapEditor {
 public:
  MidiCommandMapEditor(ApplicationCommandManager* acm, MidiCommandMap* mcm)
      : CommandMapEditor(acm, mcm), mappings_(mcm) {
  }

  virtual const String name() const;
  virtual bool isValid(const string&) const { return true; }
  virtual const String getDescription(const string&) const;
  virtual CommandID getCommand(const string&);
  virtual void removeKey(CommandID, int keyNum);
  virtual void removeKey(const string&);
  virtual void addKey(CommandID, const string&, int keyIndex);

  virtual CommandMapEditor::KeyArray getKeys(CommandID);
  virtual CommandEntryWindow* newWindow();

 private:
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiCommandMapEditor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAPEDITOR__
