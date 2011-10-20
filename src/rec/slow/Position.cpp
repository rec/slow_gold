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

Position getPosition(int c) {
  static const int SIZE = Command::BANK_SIZE;
  if (c < SIZE)
    return CURRENT;
  int base = SIZE * (c / SIZE);
  return static_cast<Position>(c - base + FIRST);
}

}  // namespace slow
}  // namespace rec
