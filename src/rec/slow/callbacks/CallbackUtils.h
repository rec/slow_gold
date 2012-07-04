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
  c->find(id)->callback_.reset(cb);
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

template <typename Proto>
void executeCallback(Instance* i, void (*protoFunction)(Proto*)) {
  const VirtualFile vf = i->file();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto);
  data::setProto(proto, vf);
}

template <typename Proto, typename Type>
void executeCallback2(Instance* i, void (*protoFunction)(Proto*, Type), Type x) {
  const VirtualFile vf = i->file();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto, x);
  data::setProto(proto, vf);
}

template <typename Proto>
void executeCallbackIf(Instance* i, bool (*protoFunction)(Proto*)) {
  const VirtualFile vf = i->file();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto))
    data::setProto(proto, vf);
}

template <typename Proto, typename Type>
void executeCallbackIf2(Instance* i, bool (*protoFunction)(Proto*, Type),
                        Type x) {
  const VirtualFile vf = i->file();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto, x))
    data::setProto(proto, vf);
}

template <typename Proto>
void addApplyCallback(CommandRecordTable* c, CommandID id,
                      bool (*protoFunction)(Proto*), Instance* i) {
  addCallback(c, id, &executeCallbackIf<Proto>, i, protoFunction);
}

template <typename Proto, typename Type>
void addApplyCallback(CommandRecordTable* c, CommandID id,
                      bool (*protoFunction)(Proto*, Type), Instance* i, Type t) {
  addCallback(c, id, &executeCallbackIf2<Proto, Type>, i, protoFunction, t);
}

template <typename Proto>
void addApplyCallback(CommandRecordTable* c, CommandID id,
                      void (*protoFunction)(Proto*), Instance* i) {
  addCallback(c, id, &executeCallback<Proto>, i, protoFunction);
}

template <typename Proto, typename Type>
void addApplyCallback(CommandRecordTable* c, CommandID id,
                      void (*protoFunction)(Proto*, Type), Type t, Instance* i) {
  addCallback(c, id, &executeCallback2<Proto, Type>, i, protoFunction, t);
}

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, CommandIDEncoder);
typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void loop(Instance*, LoopSnapshotFunction, CommandIDEncoder);
void select(Instance*, SelectorFunction, CommandIDEncoder);

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
