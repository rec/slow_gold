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
  c->addCallback(id, thread::functionCallback(f));
}

template <typename Function>
void addCallback(CallbackTable* c, CommandID id, Function f, Instance* i) {
  c->addCallback(id, thread::functionCallback(f, i));
}

template <typename Function, typename X>
void addCallback(CallbackTable* c, CommandID id, Function f, Instance* i, X x) {
  c->addCallback(id, thread::functionCallback(f, i, x));
}

template <typename Function, typename X, typename Y>
void addCallback(CallbackTable* c, CommandID id, Function f, Instance* i, X x, Y y) {
  c->addCallback(id, thread::functionCallback(f, i, x, y));
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

void loopInstance(Instance*, LoopSnapshotFunction, CommandIDEncoder);
void selectInstance(Instance*, SelectorFunction, CommandIDEncoder);
void loopNoInstance(LoopSnapshotFunction, CommandIDEncoder);
void selectNoInstance(SelectorFunction, CommandIDEncoder);

template <typename Proto>
void executeCallbackNoInstance(void (*protoFunction)(Proto*)) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto);
  data::setProto(proto, vf);
}

template <typename Proto>
void executeCallbackIfNoInstance(bool (*protoFunction)(Proto*)) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto))
    data::setProto(proto, vf);
}

template <typename Proto>
void addApplyCallback(CallbackTable* c, CommandID id,
                      void (*protoFunction)(Proto*)) {
  c->addCallback(id,
                 thread::functionCallback(&executeCallbackNoInstance<Proto>,
                                          protoFunction));
}

template <typename Proto>
void addApplyCallback(CallbackTable* c, CommandID id,
                      bool (*protoFunction)(Proto*)) {
  c->addCallback(id,
                 thread::functionCallback(&executeCallbackIfNoInstance<Proto>,
                                          protoFunction));
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_CALLBACK_UTILS__
