#include "rec/slow/Position.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

static const int SIZE = Command::BANK_SIZE;

int Position::toIndex(int32 segment, int32 size) {
  int pos = (position_ == FIRST) ? 0 :
    (position_ == PREVIOUS) ? segment - 1 :
    (position_ == CURRENT) ? segment :
    (position_ == NEXT) ? segment + 1 :
    (position_ == LAST) ? size - 1 :
    position_;
  return mod(pos, size);
}

CommandID Position::toCommandID(int32 type) {
  return (type * Command::BANK_SIZE) + (position_ - FIRST);
}

// static
Position Position::fromCommandID(CommandID id) {
  static const int SIZE = Command::BANK_SIZE;
  return Position((id < SIZE) ? CURRENT : mod(id, SIZE) + FIRST);
}

}  // namespace slow
}  // namespace rec
