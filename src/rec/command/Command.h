#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/util/thread/Callback.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandItemSetter.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

struct CommandRecord {
  explicit CommandRecord(CommandID id) : info_(id) {}

  ptr<Command> command_;
  ptr<Callback> callback_;
  ptr<CommandItemSetter> setter_;
  ApplicationCommandInfo info_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecord);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
