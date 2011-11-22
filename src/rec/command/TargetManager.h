#ifndef __REC_SLOW_COMMANDTARGET__
#define __REC_SLOW_COMMANDTARGET__

#include <map>

#include "rec/command/Command.h"
#include "rec/util/STL.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

struct CommandCallback;

// An implementation of ApplicationCommandTargetManager that lets you register commands
// with a callback.
class TargetManager : public ApplicationCommandTarget,
                      public Listener<Command::Type>,
                      public Listener<bool> {
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

  virtual void operator()(Command::Type t) {
    if (!invokeDirectly(t))
      LOG(ERROR) << "Failed to invoke " << command::Command::Type_Name(t);
  }

  virtual void operator()(bool disabled) { setDisabled(disabled); }

  // ApplicationCommandTarget virtual methods.
  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>&);
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&); // { return false; }

  InvocationInfo lastInvocation() const;

  void addCallback(CommandID id, Callback* cb,
                   const String& name,
                   const String& category, const String& desc);

  ApplicationCommandInfo* getInfo(CommandID command);
  ApplicationCommandManager* commandManager() { return &commandManager_; }
  void saveKeyboardBindings();

  void setDisabled(bool d) { Lock l(lock_); disabled_ = d; }

 private:
  typedef std::map<CommandID, CommandCallback*> CommandCallbackMap;
  void loadKeyboardBindings();

  CommandCallbackMap map_;

  ApplicationCommandManager commandManager_;
  CriticalSection lock_;
  InvocationInfo lastInvocation_;
  bool disabled_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TargetManager);
};

}  // namespace rec
}  // namespace command

#endif  // __REC_SLOW_COMMANDTARGET__
