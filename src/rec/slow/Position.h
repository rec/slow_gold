#ifndef __REC_SLOW_POSITION__
#define __REC_SLOW_POSITION__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace slow {

typedef command::Command Command;

enum Position {
  FIRST = -5, PREVIOUS = -4, CURRENT = -3, NEXT = -2, LAST = -1
};

int positionToIndex(Position pos, int segment, int size);

Position getPosition(int c);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_POSITION__
