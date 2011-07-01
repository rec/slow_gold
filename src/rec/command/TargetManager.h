#ifndef __REC_SLOW_COMMANDTARGET__
#define __REC_SLOW_COMMANDTARGET__

#include <map>

#include "rec/command/Command.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

struct CommandCallback;

// An implementation of ApplicationCommandTargetManager that lets you register commands
// with a callback.
class TargetManager : public ApplicationCommandTarget {
 public:
  explicit TargetManager(Component* comp);
  virtual ~TargetManager();

  void registerAllCommandsForTarget();
  void setApplicationCommandManagerToWatch(MenuBarModel* model) {
    model->setApplicationCommandManagerToWatch(&commandManager_);
  }

  bool invokeDirectly(CommandID commandID, bool asynchronously = false) {
    return commandManager_.invokeDirectly(commandID, asynchronously);
  }

  // ApplicationCommandTarget virtual methods.
  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }
  //  return findFirstTargetParentComponent();  // TODO

  virtual void getAllCommands(juce::Array<CommandID>&);
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&); // { return false; }

  InvocationInfo lastInvocation() const;

  void addCallback(CommandID id, Callback* cb,
                   const String& name,
                   const String& category, const String& desc);

  void addCommandItem(PopupMenu* menu, CommandID command,
                      bool isActive,
                      const String& name = String::empty);

  ApplicationCommandInfo* getInfo(CommandID command);
  ApplicationCommandManager* commandManager() { return &commandManager_; }
  void saveKeyboardBindings();

 private:
  void addCommandItem(PopupMenu* menu, CommandID command) {
    menu->addCommandItem(&commandManager_, command);
  }

  typedef std::map<CommandID, CommandCallback*> CommandMap;
  void addCallback(Callback* callback, const ApplicationCommandInfo& info);

  void loadKeyboardBindings();

  CommandMap map_;

  ApplicationCommandManager commandManager_;
  CriticalSection lock_;
  InvocationInfo lastInvocation_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TargetManager);
};

}  // namespace rec
}  // namespace command

#endif  // __REC_SLOW_COMMANDTARGET__
