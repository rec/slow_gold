#ifndef __REC_APP_PROGRAMINSTANCEIMPL__
#define __REC_APP_PROGRAMINSTANCEIMPL__

#include "rec/program/Menu.pb.h"
#include "rec/program/SetterListener.h"
#include "rec/program/Types.h"

namespace rec {
namespace program {

class JuceModel;
class Program;

class JuceModelImpl {
 public:
  JuceModelImpl(Program* p, JuceModel*);
  const MenuBar& menuBar() const;
  string addMenu(PopupMenu* popup, const string& name);
  bool perform(const InvocationInfo&);

  Program* program() { return program_; }
  JuceModel* model() { return juceModel_; }
  ApplicationCommandManager* applicationCommandManager() {
    return &applicationCommandManager_;
  }

  const ProgramMap& programMap() const { return programMap_; }

 private:
  typedef vector<unique_ptr<SetterListener>> DataListeners;

  void addSubmenu(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommands(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommand(PopupMenu* popup, CommandID);
  void addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry);
  void makeRecentFiles(PopupMenu* menu);

  Program* const program_;
  JuceModel* const juceModel_;
  ProgramMap programMap_;
  const MenuCollection menuCollection;
  const MenuMap menuMap_;
  const MenuBarMap menuBarMap_;
  DataListeners dataListeners_;
  ApplicationCommandManager applicationCommandManager_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(JuceModelImpl);
};

}  // namespace program
}  // namespace rec

#endif  // __REC_APP_PROGRAMINSTANCEIMPL__
