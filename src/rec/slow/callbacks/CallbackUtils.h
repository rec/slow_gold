#ifndef __REC_COMMAND_CALLBACK_UTILS__
#define __REC_COMMAND_CALLBACK_UTILS__

#include "rec/command/Command.h"
#include "rec/util/thread/FunctionCallback.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace slow {

class Instance;
typedef command::CommandRecordTable CommandRecordTable;
typedef command::CommandIDEncoder CommandIDEncoder;

template <typename Function>
void add(CommandRecordTable* c, int32 type, Function f) {
  command::find(c, type)->callback_.reset(thread::functionCallback(f));
}

template <typename Function>
void add(CommandRecordTable* c, int32 type, Function f, Instance* i) {
  command::find(c, type)->callback_.reset(thread::functionCallback(f, i));
}

template <typename Function, typename X>
void add(CommandRecordTable* c, int32 type, Function f, Instance* i, X x) {
  command::find(c, type)->callback_.reset(thread::functionCallback(f, i, x));
}

template <typename Function, typename X, typename Y>
void add(CommandRecordTable* c, int32 type, Function f, Instance* i, X x, Y y) {
  command::find(c, type)->callback_.reset(thread::functionCallback(f, i, x, y));
}

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, CommandIDEncoder);
typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void loop(Instance*, LoopSnapshotFunction, CommandIDEncoder);
void select(Instance*, SelectorFunction, CommandIDEncoder);

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
