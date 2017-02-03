#pragma once

#include "rec/program/Program.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

template <typename Function>
void addCallback(program::Program* c, CommandID id, Function f) {
    c->addCallback(id, thread::functionCB(f));
}

template <typename Function, typename X>
void addCallback(program::Program* c, CommandID id, Function f, X x) {
    c->addCallback(id, thread::functionCB(f, x));
}

}  // namespace slow
}  // namespace rec
