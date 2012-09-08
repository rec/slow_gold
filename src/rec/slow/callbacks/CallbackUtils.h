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
                      bool (*protoFunction)(Proto*, Type), Type t, Instance* i) {
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

template <typename Functor, typename Proto>
void execute1(Functor file, void (*protoFunction)(Proto*)) {
  const VirtualFile vf = file();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto);
  data::setProto(proto, vf);
}

template <typename Functor, typename Proto, typename Type>
void execute2(Functor file, void (*protoFunction)(Proto*), Type t) {
  const VirtualFile vf = file();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto, t);
  data::setProto(proto, vf);
}

template <typename Functor, typename Proto>
void executeIf1(Functor file, void (*protoFunction)(Proto*)) {
  const VirtualFile vf = file();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto))
    data::setProto(proto, vf);
}

template <typename Functor, typename Proto, typename Type>
void executeIf2(Functor file, void (*protoFunction)(Proto*), Type t) {
  const VirtualFile vf = file();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto, t))
    data::setProto(proto, vf);
}

template <typename Functor, typename Proto>
Callback* makeCallback(Functor file, void (*fn)(Proto*)) {
  return thread::functionCallback(&execute1<Functor, Proto>, file, fn);
}

template <typename Functor, typename Proto>
Callback* makeCallback(Functor file, bool (*fn)(Proto*)) {
  return thread::functionCallback(&executeIf1<Functor, Proto>, file, fn);
}

template <typename Functor, typename Proto, typename Type>
Callback* makeCallback(Functor file, void (*fn)(Proto*, Type t), Type t) {
  return thread::functionCallback(&execute1<Functor, Proto>, file, fn, t);
}

template <typename Functor, typename Proto, typename Type>
Callback* makeCallback(Functor file, bool (*fn)(Proto*, Type t), Type t) {
  return thread::functionCallback(&executeIf1<Functor, Proto>, file, fn, t);
}

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, CommandIDEncoder);
typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void loop(Instance*, LoopSnapshotFunction, CommandIDEncoder);
void select(Instance*, SelectorFunction, CommandIDEncoder);
void loopNoInstance(LoopSnapshotFunction, CommandIDEncoder);
void selectNoInstance(SelectorFunction, CommandIDEncoder);

template <typename Proto>
void executeCallbackNoInstance(void (*protoFunction)(Proto*)) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto);
  data::setProto(proto, vf);
}

template <typename Proto, typename Type>
void executeCallback2NoInstance(void (*protoFunction)(Proto*, Type), Type x) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto, x);
  data::setProto(proto, vf);
}

template <typename Proto>
void executeCallbackIfNoInstance(bool (*protoFunction)(Proto*)) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto))
    data::setProto(proto, vf);
}

template <typename Function, typename X>
void addCallbackNoInstance(CommandRecordTable* c, CommandID id, Function f, X x) {
  addCallback(c, id, thread::functionCallback(f, x));
}

template <typename Proto>
void addApplyCallback(CommandRecordTable* c, CommandID id,
                      void (*protoFunction)(Proto*)) {
  addCallbackNoInstance(c, id, &executeCallbackNoInstance<Proto>,
                        protoFunction);
}


}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
