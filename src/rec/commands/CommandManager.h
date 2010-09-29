#ifndef __REC_COMMANDS_COMMANDMANAGER__
#define __REC_COMMANDS_COMMANDMANAGER__

#include "rec/base/basictypes.h"
#include "rec/util/PointerList.h"

namespace rec {
namespace commands {

class MenuDelegate {
 public:
  virtual bool getMenuBarNames(StringArray* array) { return false; }
  virtual bool getMenuForIndex(PopupMenu* menu, int i, const String& name) {
    return false;
  }
  virtual ~MenuDelegate() {}
};

class MultiMenu : public MenuBarModel, public util::PointerList<MenuDelegate> {
 public:
  virtual const StringArray getMenuBarNames() {
    StringArray result;
    forEach(MultiMenu::getMenuBarNames, &result);
    return result;
  }

  virtual const PopupMenu getMenuForIndex(int index, const String& name) {
    PopupMenu result;
    forEach(MultiMenu::getMenuForIndex, &result, index, name);
    return result;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(MultiMenu);
};

class CommandDelegate {
 public:
  virtual bool menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    return false;
  }
  virtual bool getAllCommands(Array <CommandID>* commands) { return false; }
  virtual bool getCommandInfo(CommandID id, ApplicationCommandInfo& result) {
    return false;
  }
  virtual bool perform(const InvocationInfo& info) { return false; }
};

class MultiCommand : public ApplicationCommandTarget, public PointerList<CommandDelegate> {
 public:
  MultiMenu(CommandDelegate** begin, CommandDelegate** end)
      : PointerList<CommandDelegate>(begin, end) {
  }

  virtual void menuItemSelected(int itemID, int menuIndex) {
    forEach(MultiMenu::menuItemSelected, itemId, menuIndex));
  }

  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    forEach(MultiMenu::getCommandInfo, id, info);
  }

  virtual void getAllCommands(Array <CommandID>& commands) {
    forEach(MultiMenu::getAllCommands, &commands);
  }

  virtual bool perform(const InvocationInfo& info) {
    return forEach(MultiMenu::perform, info);
  }

  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(MultiCommand);
};

}  // namespace commands
}  // namespace rec

#endif  // __REC_COMMANDS_COMMANDMANAGER__
