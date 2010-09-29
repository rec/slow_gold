#ifndef __REC_PERSIST_COMMANDMANAGER__
#define __REC_PERSIST_COMMANDMANAGER__

#include "rec/base/basictypes.h"

namespace rec {
namespace persist {

class MultiMenu : public MenuBarModel {
 public:
  class Delegate {
    virtual void getMenuBarNames(StringArray* array) = 0;
    virtual void getMenuForIndex(PopupMenu* menu, int i, const String& name) = 0;
  };

  MultiMenu(Delegate** begin, Delegate** end) : delegates_(begin, end) {}

  virtual const StringArray getMenuBarNames() {
    StringArray result;

    for (Delegate** i = begin(); i != end(); ++i)
      (*i)->addMenuBarNames(&result);

    return result;
  }

  virtual const PopupMenu getMenuForIndex(int index, const String& name) {
    PopupMenu result;

    for (Delegate** i = begin(); i != end(); ++i)
      (*i)->getMenuForIndex(&result, index, name);

    return result;
  }

 private:
  Delegate** begin() { return &*delegates.begin(); }
  Delegate** end() { return &*delegates.end(); }

  typedef std::vector<Delegate*> DelegateList;
  DelegateList delegates_;
};

class MultiCommand : public ApplicationCommandTarget {
 public:
  class Delegate {
   public:
    virtual bool menuItemSelected(int menuItemID, int topLevelMenuIndex) = 0;
    virtual void getAllCommands(Array <CommandID>* commands) = 0;
    virtual bool getCommandInfo(CommandID id, ApplicationCommandInfo& result) = 0;
    virtual bool perform(const InvocationInfo& info) = 0;
  };

  MultiMenu(Delegate** begin, Delegate** end) : delegates_(begin, end) {}

  // ApplicationCommandTarget virtual methods.
  virtual void menuItemSelected(int itemID, int menuIndex) {
    Delegate** i = begin();
    for (; i != end() && !(*i)->menuItemSelected(itemID, menuIndex); ++i);
  }

  // ApplicationCommandTarget virtual methods.
  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    Delegate** i = begin();
    for (; i != end() && !(*i)->getCommandInfo(id, info); ++i);
  }

  virtual void getAllCommands(Array <CommandID>& commands) {
    for (Delegate** i = begin(); i != end(); ++i)
      (*i)->getAllCommands(&commands);
  }

  virtual bool perform(const InvocationInfo& info) {
    for (Delegate** i = begin(); i != end(); ++i) {
      if ((*i)->perform(info))
        return true;
    }
    return false;
  }

  virtual ApplicationCommandTarget* getNextCommandTarget() {
    return NULL;
  }

 private:
  Delegate** begin() { return &*delegates.begin(); }
  Delegate** end() { return &*delegates.end(); }

  typedef std::vector<Delegate*> DelegateList;
  DelegateList delegates_;
};

#ifdef PROBABLY_DELETE_THIS

class CommandManager : public ApplicationCommandTarget,
                       public MenuBarModel {
 public:
  CommandManager(ApplicationCommandTarget* appTarget, MenuBarModel* menuModel)
      : appTarget_(appTarget), menuModel_(menuModel) {
  }

  // MenuBarModel virtual methods.
  virtual const StringArray getMenuBarNames() {
    StringArray result = menuModel_->getMenuBarNames();
    delegate_->addMenuBarNames(&result);
    return result;
  }

  virtual const PopupMenu getMenuForIndex(int index, const String& name) {
    StringArray result = menuModel_->getMenuForIndex(index, name);
    delegate_->addMenuForIndex(&result, index, name);
    return result;
  }

  // ApplicationCommandTarget virtual methods.
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}
  virtual void getAllCommands(Array <CommandID>& commands) {}
  virtual void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) {}
  virtual bool perform(const InvocationInfo& info) { return false; }

  virtual ApplicationCommandTarget* getNextCommandTarget() {
    return NULL;
  }

  juce_UseDebuggingNewOperator

 private:
  ApplicationCommandManager commandManager_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CommandManager);
};

#endif

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_COMMANDMANAGER__
