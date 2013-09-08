#ifndef __REC_COMMAND_CALLBACKTABLE__
#define __REC_COMMAND_CALLBACKTABLE__

#include "rec/command/ID.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

class CallbackTable {
 public:
  CallbackTable() {}
  virtual ~CallbackTable() {}

  virtual void addCallback(ID, unique_ptr<Callback>) = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CallbackTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACKTABLE__
