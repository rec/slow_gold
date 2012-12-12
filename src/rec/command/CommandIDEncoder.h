#ifndef __REC_COMMAND_COMMANDIDENCODER__
#define __REC_COMMAND_COMMANDIDENCODER__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace command {

typedef command::Command Command;

class CommandIDEncoder {
 public:
  enum Special {
    FIRST = -5, PREVIOUS = -4, CURRENT = -3, NEXT = -2, LAST = -1
  };

  CommandIDEncoder() {}
  CommandIDEncoder(int32 p) : position_(p) {}
  CommandIDEncoder(Special p) : position_(p) {}

  CommandID toCommandID(int32 type);

  int32 position_;
};

int toCommandID(const Command&);
void fillCommandFromId(CommandID, Command*);
CommandIDEncoder fromCommandID(CommandID);
CommandID toCommandID(int32 position, int32 type);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDIDENCODER__
