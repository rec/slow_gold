#ifndef __REC_SLOW_COMMANDTARGET__
#define __REC_SLOW_COMMANDTARGET__

#include <map>

#include "rec/base/STL.h"

namespace rec {
namespace command {

class Callback

}  // namespace rec
}  // namespace command

namespace rec {
namespace command {

struct CommandCallback;

// An implementation of ApplicationCommandTargetManager that lets you register commands
// with a callback.
class TargetManager : public ApplicationCommandTargetManager {
 public:
  explicit TargetManager(Component* c = NULL);
  void addComponent(Component* c);

  // ApplicationTargetManager virtual methods.
  virtual void getAllCommands(Array<CommandID>&);
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&); // { return false; }

  InvocationInfo lastInvocation() const;

  void add(thread::Callback* callback, const ApplicationCommandInfo& info);

  void add(CommandID id, thread::Callback* cb,
           const String& name,
           const String& category, const String& desc,
           int keyCode = 0,
           const ModifierKeys& modifiers = getDefaultMods(),
           int flags = 0);

  void addCommandItem(PopupMenu* menu, CommandID command) {
    menu->addCommandItem(commandManager_, command);
  }


 private:
  typedef std::hash_map<juce::CommandID, CommandCallback*> CommandMap;

  CommandMap map_;

  ApplicationCommandManager commandManager_;
  CriticalSection lock_;
  InvocationInfo lastInvocation_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TargetManager);
};

}  // namespace rec
}  // namespace command

#endif  // __REC_SLOW_COMMANDTARGET__
