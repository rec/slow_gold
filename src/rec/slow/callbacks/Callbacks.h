#ifndef __REC_COMMAND_CALLBACKS__
#define __REC_COMMAND_CALLBACKS__

#include "rec/command/Command.h"
#include "rec/util/thread/FunctionCallback.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/slow/Position.h"

namespace rec {
namespace slow {

class Instance;
typedef command::CallbackTable CallbackTable;

template <typename Function>
void add(CallbackTable* c, int32 type, Function f) {
  (*c)[type] = thread::functionCallback(f);
}

template <typename Function>
void add(CallbackTable* c, int32 type, Function f, Instance* i) {
  (*c)[type] = thread::functionCallback(f, i);
}

template <typename Function, typename V1>
void add(CallbackTable* c, int32 type, Function f, Instance* i, V1 v1) {
  (*c)[type] = thread::functionCallback(f, i, v1);
}

template <typename Function, typename V1, typename V2>
void add(CallbackTable* c, int32 type, Function f, Instance* i, V1 v1, V2 v2) {
  (*c)[type] = thread::functionCallback(f, i, v1, v2);
}

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, Position);
typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void loop(Instance*, LoopSnapshotFunction, Position);
void select(Instance*, SelectorFunction, Position);

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACKS__
