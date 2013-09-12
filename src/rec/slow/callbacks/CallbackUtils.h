#ifndef __REC_COMMAND_CALLBACK_UTILS__
#define __REC_COMMAND_CALLBACK_UTILS__

#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

using command::CallbackTable;

template <typename Function>
void addCallback(CallbackTable* c, CommandID id, Function f) {
  c->addCallback(id, thread::functionCB(f));
}

template <typename Function, typename X>
void addCallback(CallbackTable* c, CommandID id, Function f, X x) {
  c->addCallback(id, thread::functionCB(f, x));
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
