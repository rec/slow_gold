#ifndef __REC_SLOW_POSITION__
#define __REC_SLOW_POSITION__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace slow {

typedef command::Command Command;

// We repeat "first" to make it easy to have uniform menus.
enum Position { FIRST = -5, PREVIOUS = -4, CURRENT = -3, NEXT = -2, LAST = -1, ZERO = 0 };
static const int SLOT_COUNT = 10;

int positionToIndex(Position pos, int segment, int size);

Command::Type getCommandBase(Command::Type);
Position getPosition(Command::Type);

Command::Type getCommand(Command::Type base, Position);


}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_POSITION__