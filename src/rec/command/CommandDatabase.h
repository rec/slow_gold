#ifndef __REC_COMMAND_COMMANDDATABASE__
#define __REC_COMMAND_COMMANDDATABASE__

#include "rec/command/Command.h"

namespace rec {
namespace command {

class CommandDatabase {
 public:
  CommandDatabase();
  ~CommandDatabase();
  void clear();

  const Command command(CommandID id) const;
  const CommandContext& context() const { return context_; }

  void recalculate();

 private:
  CriticalSection lock_;
  CommandContext context_;

  DISALLOW_COPY_AND_ASSIGN(CommandDatabase);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATABASE__
