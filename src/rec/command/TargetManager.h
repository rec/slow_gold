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
  explicit TargetManager(Component* c = NULL);
  void registerAllCommandsForTarget();
  void addComponent(Component* c);

  // ApplicationCommandTarget virtual methods.
  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }
  //  return findFirstTargetParentComponent();

  virtual void getAllCommands(juce::Array<CommandID>&);
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&); // { return false; }

  InvocationInfo lastInvocation() const;

  void add(Callback* callback, const ApplicationCommandInfo& info);

  void add(CommandID id, Callback* cb,
           const String& name,
           const String& category, const String& desc,
           int keyCode = 0,
           const ModifierKeys& modifiers = getDefaultMods(),
           int flags = 0);

  void addCommandItem(PopupMenu* menu, CommandID command) {
    menu->addCommandItem(&commandManager_, command);
  }

 private:
  typedef std::map<CommandID, CommandCallback*> CommandMap;

  CommandMap map_;

  ApplicationCommandManager commandManager_;
  CriticalSection lock_;
  InvocationInfo lastInvocation_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TargetManager);
};

}  // namespace rec
}  // namespace command

#endif  // __REC_SLOW_COMMANDTARGET__
