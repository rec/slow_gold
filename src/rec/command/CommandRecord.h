#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/util/thread/Callback.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandItemSetter.h"
#include "rec/command/ID.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandRecord {
 public:
  explicit CommandRecord(ID id) : info_(id) {}

  ApplicationCommandInfo* getInfo() { return &info_; }
  void fillInfo();

  ApplicationCommandInfo info_;

  unique_ptr<Command> command_;
  unique_ptr<Callback> callback_;
  unique_ptr<CommandItemSetter> setter_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecord);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
