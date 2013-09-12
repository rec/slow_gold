#ifndef __REC_COMMAND_COMMANDDATA__
#define __REC_COMMAND_COMMANDDATA__

#include "rec/Command/CommandRecord.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CallbackTable;

class CommandData {
 public:
  CommandData() {}
  virtual ~CommandData() {}

  virtual const Commands& allCommands() const = 0;
  virtual void addCallbacks(CallbackTable*) const = 0;
};
}
  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATA__
