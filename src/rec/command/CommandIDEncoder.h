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

  int32 toIndex(int32 segment, int32 size);
  CommandID toCommandID(int32 type);

  static CommandID toCommandID(int32 position, int32 type) {
    return CommandIDEncoder(position).toCommandID(type);
  }

  static void fillCommandFromId(CommandID, Command*);

  static CommandIDEncoder fromCommandID(CommandID);
  static Command::Type getType(CommandID);
  static string commandIDName(CommandID);
  static int toCommandID(const Command&);

  static bool isA(int32 id, Command::Type type);

  operator int32() const { return position_; }
  int32 getPosition() const { return position_; }

 private:
  int32 position_;
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDIDENCODER__
