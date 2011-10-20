#ifndef __REC_COMMAND_CALLBACKS__
#define __REC_COMMAND_CALLBACKS__

#include "rec/slow/LoopSnapshot.h"
#include "rec/util/thread/FunctionCallback.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Position.h"

namespace rec {
namespace slow {

class Instance;

template <typename Function>
void add(CallbackTable* c, int32 type, Function f) {
  (*c)[type] = functionCallback(f);
}

template <typename Function>
void add(CallbackTable* c, int32 type, Function f, Instance* i) {
  (*c)[type] = functionCallback(f, i);
}

template <typename Function, typename V1>
void add(CallbackTable* c, int32 type, Function f, Instance* i, V1 v1) {
  (*c)[type] = functionCallback(f, i, v1);
}

template <typename Function, typename V1, typename V2>
void add(CallbackTable* c, int32 type, Function f, Instance* i, V1 v1, V2 v2) {
  (*c)[type] = functionCallback(f, i, v1, v2);
}

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, Position);
typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void loop(LoopSnapshotFunction, Instance*, Position);
void select(SelectorFunction, Instance*, Position);

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACKS__
