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

inline void addCallback(CommandRecordTable* c, CommandID id, Callback* cb) {
  DLOG(INFO) << "Adding callback " << command::commandName(id);
  command::find(c, id)->callback_.reset(cb);
}

template <typename Function>
void addCallback(CommandRecordTable* c, CommandID id, Function f) {
  addCallback(c, id, thread::functionCallback(f));
}

template <typename Function>
void addCallback(CommandRecordTable* c, CommandID id, Function f, Instance* i) {
  addCallback(c, id, thread::functionCallback(f, i));
}

template <typename Function, typename X>
void addCallback(CommandRecordTable* c, CommandID id, Function f, Instance* i, X x) {
  addCallback(c, id, thread::functionCallback(f, i, x));
}

template <typename Function, typename X, typename Y>
void addCallback(CommandRecordTable* c, CommandID id, Function f, Instance* i, X x, Y y) {
  addCallback(c, id, thread::functionCallback(f, i, x, y));
}

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, CommandIDEncoder);
typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void loop(Instance*, LoopSnapshotFunction, CommandIDEncoder);
void select(Instance*, SelectorFunction, CommandIDEncoder);

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
