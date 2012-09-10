#ifndef __REC_COMMAND_CALLBACKTABLE__
#define __REC_COMMAND_CALLBACKTABLE__

#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

class CallbackTable {
 public:
  CallbackTable() {}
  virtual void addCallback(CommandID id, Callback* cb) = 0;
  virtual ~CallbackTable() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CallbackTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACKTABLE__
