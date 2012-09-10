#ifndef __REC_COMMAND_CALLBACK_UTILS__
#define __REC_COMMAND_CALLBACK_UTILS__

#include "rec/command/Command.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

class Instance;
using command::CallbackTable;
using command::CommandRecordTable;
using command::CommandIDEncoder;

template <typename Function>
void addCallback(CallbackTable* c, CommandID id, Function f) {
  c->addCallback(id, thread::functionCB(f));
}

template <typename Function>
void addCallback(CallbackTable* c, CommandID id, Function f, Instance* i) {
  c->addCallback(id, thread::functionCB(f, i));
}

template <typename Function, typename X>
void addCallback(CallbackTable* c, CommandID id, Function f, Instance* i, X x) {
  c->addCallback(id, thread::functionCB(f, i, x));
}

template <typename Function, typename X, typename Y>
void addCallback(CallbackTable* c, CommandID id, Function f, Instance* i, X x, Y y) {
  c->addCallback(id, thread::functionCB(f, i, x, y));
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
