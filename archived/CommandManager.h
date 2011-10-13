#ifndef __REC_COMMANDS_COMMANDMANAGER__
#define __REC_COMMANDS_COMMANDMANAGER__

#include "rec/base/base.h"
#include "rec/util/PointerList.h"

namespace rec {
namespace commands {

typedef ApplicationCommandTarget::InvocationInfo InvocationInfo;

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
    forEach(&MenuDelegate::getMenuBarNames, &result, true);
    return result;
  }

  virtual const PopupMenu getMenuForIndex(int index, const String& name) {
    PopupMenu result;
    forEach(&MenuDelegate::getMenuForIndex, &result, index, name, true);
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
  virtual bool getCommandInfo(CommandID id, ApplicationCommandInfo* result) {
    return false;
  }
  virtual bool perform(const InvocationInfo& info) { return false; }
  virtual ~CommandDelegate() {}
};

class MultiCommand : public ApplicationCommandTarget,
                     public util::PointerList<CommandDelegate> {
 public:
  virtual void menuItemSelected(int itemID, int menuIndex) {
    forEach(&CommandDelegate::menuItemSelected, itemID, menuIndex, true);
  }

  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    forEach(&CommandDelegate::getCommandInfo, id, &info, true);
  }

  virtual void getAllCommands(Array <CommandID>& commands) {
    forEach(&CommandDelegate::getAllCommands, &commands, true);
  }

  virtual bool perform(const InvocationInfo& info) {
    return forEach(&CommandDelegate::perform, info, false);
  }

  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(MultiCommand);
};

}  // namespace commands
}  // namespace rec

#endif  // __REC_COMMANDS_COMMANDMANAGER__
