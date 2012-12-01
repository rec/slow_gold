#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

class KeyCommandMapEditor : public CommandMapEditor {
 public:
  KeyCommandMapEditor(ApplicationCommandManager* acm, KeyPressMappingSet* mcm)
      : CommandMapEditor(acm, mcm), mappings_(mcm) {
  }

  virtual const String name() const;
  virtual bool isValid(const string&) const;
  virtual const String getDescription(const string&) const;
  virtual CommandID getCommand(const string&);

  virtual void removeKey(CommandID, int keyNum);
  virtual void removeKey(const string&);
  virtual void addKey(CommandID, const string&, int keyIndex);

  virtual CommandMapEditor::KeyArray getKeys(CommandID);
  virtual CommandEntryWindow* newWindow();

 private:
  KeyPressMappingSet* mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(KeyCommandMapEditor);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
