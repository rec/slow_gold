#ifndef __REC_COMMAND_COMMANDTARGET__
#define __REC_COMMAND_COMMANDTARGET__

// CommandTarget is the implementation of Juce's ApplicationCommandTarget for
// this application.

#include "rec/slow/HasInstance.h"

namespace rec {
namespace command {

class CommandTarget : public ApplicationCommandTarget,
                      public slow::HasInstance {
 public:
  CommandTarget(slow::Instance* i) : slow::HasInstance(i) {}
  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>&);

  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&);

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandTarget);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDTARGET__
