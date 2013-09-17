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
  ~JuceModelImpl() { stopThreads(); }

  const MenuBar& menuBar() const;
  string addMenu(PopupMenu* popup, const string& name);
  bool perform(const InvocationInfo&);

  Program* program() { return program_; }
  JuceModel* model() { return juceModel_; }

  StringArray getMenuBarNames();
  const CommandMap& commandMap() const { return commandMap_; }
  void getCommandInfo(CommandID, ApplicationCommandInfo*);

  PopupMenu getMenuForIndex(int menuIndex);

  void startThreads();
  void stopThreads();
  Thread* getThread(const string&);

 private:
  typedef vector<unique_ptr<SetterListener>> DataListeners;

  void addSubMenu(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommands(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommand(PopupMenu* popup, CommandID, bool hasIndex=false);
  void addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry);
  void makeRecentFiles(PopupMenu* menu);
  bool isRecentFiles(CommandID) const;

  void addSingleCommand(PopupMenu* popup, CommandID id);

  Program* const program_;
  JuceModel* const juceModel_;

  CommandMap commandMap_;
  const MenuMap menuMap_;
  const MenuBarMap menuBarMap_;
  const LayoutMap layoutMap_;
  const ComponentMap componentMap_;
  ThreadMap threadMap_;

  DataListeners dataListeners_;
  CommandID recentFiles_;
  CommandID recentFilesEnd_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(JuceModelImpl);
};

}  // namespace program
}  // namespace rec

#endif  // __REC_APP_PROGRAMINSTANCEIMPL__
