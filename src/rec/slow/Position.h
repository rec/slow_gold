#ifndef __REC_SLOW_POSITION__
#define __REC_SLOW_POSITION__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace slow {

typedef command::Command Command;

class Position {
 public:
  enum Special {
    FIRST = -5, PREVIOUS = -4, CURRENT = -3, NEXT = -2, LAST = -1
  };

  Position() {}
  Position(int32 p) : position_(p) {}
  Position(Special p) : position_(p) {}

  int32 toIndex(int32 segment, int32 size);
  CommandID toCommandID(int32 type);

  static Position fromCommandID(CommandID id);
  operator int32() const { return position_; }

 private:
  int32 position_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_POSITION__
