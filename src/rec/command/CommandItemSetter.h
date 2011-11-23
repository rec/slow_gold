#ifndef __REC_COMMAND_COMMANDITEMSETTER__
#define __REC_COMMAND_COMMANDITEMSETTER__

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandItemSetter {
 public:
  CommandItemSetter() {}
  virtual ~CommandItemSetter() {}
  virtual string menuName() const = 0;
  virtual void execute() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(CommandItemSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDITEMSETTER__
