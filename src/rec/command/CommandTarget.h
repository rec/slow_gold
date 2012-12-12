#ifndef __REC_COMMAND_COMMANDTARGET__
#define __REC_COMMAND_COMMANDTARGET__

// CommandTarget is the implementation of Juce's ApplicationCommandTarget for
// this application.

#include "rec/command/ID.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandTarget : public slow::HasInstance,
                      public ApplicationCommandTarget,
                      public Listener<ID>,
                      public Listener<Enable> {
 public:
  CommandTarget(slow::Instance* i) : slow::HasInstance(i), enable_(ENABLE) {}
  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>&);
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&);

  virtual void operator()(ID);
  virtual void operator()(Enable);

  CriticalSection lock_;
  Enable enable_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandTarget);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDTARGET__
