#ifndef __REC_COMMAND_COMMANDITEMSETTER__
#define __REC_COMMAND_COMMANDITEMSETTER__

#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

class CommandItemSetter : public Callback {
 public:
  CommandItemSetter() {}
  virtual ~CommandItemSetter() {}
  virtual string menuName() const = 0;
  virtual bool operator()() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(CommandItemSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDITEMSETTER__
