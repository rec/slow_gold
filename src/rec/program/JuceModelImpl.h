#ifndef __REC_APP_PROGRAMINSTANCEIMPL__
#define __REC_APP_PROGRAMINSTANCEIMPL__

#include "rec/program/Menu.pb.h"
#include "rec/program/JuceModel.h"
#include "rec/program/Types.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace program {

class Program;

class JuceModel::Impl {
 public:
  Impl(Program* p);
  const MenuBar& menuBar() const;
  string addMenu(PopupMenu* popup, const string& name);
  bool perform(const InvocationInfo&);

  Program* program() { return program_; }
  ApplicationCommandManager* applicationCommandManager() {
    return &applicationCommandManager_;
  }

  const ProgramMap& programMap() const { return programMap_; }

  void updateMenus();

 private:
  void addSubmenu(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommands(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommand(PopupMenu* popup, CommandID);
  void addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry);
  void makeRecentFiles(PopupMenu* menu);

  Program* program_;
  ProgramMap programMap_;
  const MenuCollection menuCollection;
  const MenuMap menuMap_;
  const MenuBarMap menuBarMap_;
  DataListeners dataListeners_;
  ApplicationCommandManager applicationCommandManager_;
};

}  // namespace program
}  // namespace rec

#endif  // __REC_APP_PROGRAMINSTANCEIMPL__
