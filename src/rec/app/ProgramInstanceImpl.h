#ifndef __REC_APP_PROGRAMINSTANCEIMPL__
#define __REC_APP_PROGRAMINSTANCEIMPL__

#include "rec/app/Menu.pb.h"
#include "rec/app/ProgramInstance.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace app {

class Program;

class ProgramInstance::Impl {
 public:
  Impl(Program* p);
  const MenuBar& menuBar() const;
  void addSubmenu(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommands(PopupMenu* popup, const MenuEntry& menuEntry);
  void addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry);
  string addMenu(PopupMenu* popup, const string& name);

  Program* program() { return program_; }
  ApplicationCommandManager* applicationCommandManager() {
    return &applicationCommandManager_;
  }

  typedef std::unordered_map<CommandID, command::Command> ProgramMap;
  typedef std::unordered_map<string, Menu> MenuMap;
  typedef std::unordered_map<string, MenuBar> MenuBarMap;
  const ProgramMap& programMap() const { return programMap_; }

 private:
  Program* program_;
  ProgramMap programMap_;
  const MenuCollection menuCollection;
  const MenuMap menuMap_;
  const MenuBarMap menuBarMap_;
  ApplicationCommandManager applicationCommandManager_;
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_PROGRAMINSTANCEIMPL__
