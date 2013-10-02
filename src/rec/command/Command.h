#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/base/base.h"

namespace rec {
namespace command {

class Command {
 public:
  Command();

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Command);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
