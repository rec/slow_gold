#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/util/thread/Callback.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandItemSetter.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

struct CommandRecord {
  CommandRecord() {}

  ptr<Command> command_;
  ptr<Callback> callback_;
  ptr<CommandItemSetter> setter_;
  ptr<ApplicationCommandInfo> info_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecord);
};

typedef std::map<CommandID, CommandRecord*> CommandRecordTable;

const CommandRecordTable makeCommandRecordTable(Listener<None>*);

CommandRecord* find(CommandRecordTable* table, CommandID id);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
