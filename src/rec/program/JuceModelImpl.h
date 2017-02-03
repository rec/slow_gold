#pragma once

#include "rec/command/map/CommandMap.pb.h"
#include "rec/gui/proto/Constants.h"
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
  const command::CommandMapProto& keyMap() const { return keyMap_; }
  const gui::Constants& constants() const { return constants_; }
  const gui::Layout& getLayout(const string& n) const {
    return layoutMap_.at(n);
  }

 private:
  typedef vector<unique_ptr<SetterListener>> DataListeners;

  void addSubMenu(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommands(PopupMenu* popup, const MenuEntry& menuEntry);
  void addCommand(PopupMenu* popup, CommandID, bool hasIndex=false);
  void addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry);

  void logMaps();

  void makeRecentFiles(PopupMenu* menu);
  bool isRecentFiles(CommandID) const;

  void addSingleCommand(PopupMenu* popup, CommandID id);

  Program* const program_;
  JuceModel* const juceModel_;

  CommandMap commandMap_;
  command::CommandMapProto keyMap_;
  const MenuMap menuMap_;
  const MenuBarMap menuBarMap_;
  const LayoutMap layoutMap_;
  ThreadMap threadMap_;
  gui::Constants constants_;

  DataListeners dataListeners_;
  CommandID recentFiles_;
  CommandID recentFilesEnd_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(JuceModelImpl);
};

}  // namespace program
}  // namespace rec

