#ifndef __REC_APP_PROGRAMINSTANCEIMPL__
#define __REC_APP_PROGRAMINSTANCEIMPL__

#include "rec/program/Menu.pb.h"
#include "rec/program/ProgramInstance.h"
#include "rec/command/Command.pb.h"
#include "rec/data/UntypedDataListener.h"

namespace rec {
namespace app {

class Program;

class ProgramInstance::Impl {
 public:
  Impl(Program* p);
  const MenuBar& menuBar() const;
  string addMenu(PopupMenu* popup, const string& name);
  bool perform(const InvocationInfo&);

  Program* program() { return program_; }
  ApplicationCommandManager* applicationCommandManager() {
    return &applicationCommandManager_;
  }

  typedef std::unordered_map<CommandID, command::Command> ProgramMap;
  typedef std::unordered_map<string, Menu> MenuMap;
  typedef std::unordered_map<string, MenuBar> MenuBarMap;
  typedef vector<unique_ptr<UntypedDataListener>> DataListeners;

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

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_PROGRAMINSTANCEIMPL__
