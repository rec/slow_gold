#include "rec/slow/Threads.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/STL.h"

namespace rec {
namespace slow {

static const int THREAD_STOP_PERIOD = 5000;

void clock(Instance* i) { (*i->listeners_)(i->player_->getNextReadPosition()); }
void browser(Instance* i) { i->components_->directoryTree_.checkVolumes(); }
void fetch(Instance* i) {}

void parameter(Instance* i) {
  ScopedLock l(*i->threads_->lock());

}

void persist(Instance* i) {}
void pitch(Instance* i) {}

Threads::Threads(Instance* i) : instance_(i) {}

void Threads::startAll() {
  start(&clock, "Clock");
  start(&browser, "Browser", 1000);
  start(&fetch, "Fetch");
  start(&parameter, "Parameter");
  start(&persist, "Persist");
  start(&pitch, "Pitch");
}

Threads::~Threads() {
  stop();
  stl::deletePointers(&threads_);
}

void Threads::stop() {
  for (int i = 0; i < threads_.size(); ++i)
    threads_[i]->stopThread(THREAD_STOP_PERIOD);
}

void Threads::start(InstanceFunction f, const String& name, int wait) {
  ptr<Callback> cb(makePointer(f, instance_));
  Thread* t(thread::makeLoop(wait, name, cb.transfer()));
  threads_.push_back(t);
  t->startThread();
}

}  // namespace slow
}  // namespace rec
