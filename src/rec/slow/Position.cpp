#include "rec/slow/Position.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

static const int SIZE = Command::BANK_SIZE;

int positionToIndex(Position pos, int segment, int size) {
  return mod((pos == FIRST) ? 0 :
             (pos == PREVIOUS) ? segment - 1 :
             (pos == CURRENT) ? segment :
             (pos == NEXT) ? segment + 1 :
             (pos == LAST) ? size - 1 :
             static_cast<int>(pos),
             size);
}

int commandToIndex(const Command& cmd, int index) {
  Command::Type t = cmd.type();
  return cmd.repeat_count() ? Command::BANK_SIZE * t + index: t;
}


#if 0

namespace {


const int START = Command::BANK_START;
const int END = Command::BANK_END;

bool isBank(Command::Type c) { return (c >= START && c < END); }


Command::Type base(Command::Type c) {
  return static_cast<Command::Type>(SIZE * (c / SIZE));
}

Command::Type getCommandBase(Command::Type c) {
  return isBank(c) ? base(c) : c;
}

Command::Type getCommand(Command::Type c, Position p) {
  return isBank(c) ? static_cast<Command::Type>(c + p - FIRST) : c;
}

Position getPosition(Command::Type c) {
  return isBank(c) ? static_cast<Position>(c - base(c) + FIRST) : CURRENT;
}

}  // namespace


#endif

}  // namespace slow
}  // namespace rec
