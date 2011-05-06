#include "rec/slow/Threads.h"
//#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Threads.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace slow {

using namespace rec::audio::stretch;
using namespace rec::audio::util;
using namespace rec::util::thread;

static const int THREAD_STOP_PERIOD = 5000;

void browser(Instance* i) { i->components_->directoryTree_.checkVolumes(); }
void fetch(Instance* i) { i->model_->fillOnce(); }
void updateParameters(Instance* i) { i->model_->checkChanged(); }

void persist(Instance* i) {}
void pitch(Instance* i) {}


Threads::Threads(Instance* i) : HasInstance(i), fetchThread_(NULL) {}

void Threads::startAll() {
  start(&browser, "Browser", 1000);
	fetchThread_ = start(&fetch, "Fetch", 10);
  start(&updateParameters, "Parameter", 100);
  // start(&persist, "Persist", 100);
  // start(&pitch, "Pitch", 100);

  (*model()->fileLocker())(persist::get<VirtualFile>());
}

Threads::~Threads() {
  stop();
  stl::deletePointers(&threads_);
}

void Threads::stop() {
  for (int i = 0; i < threads_.size(); ++i) {
    VLOG(1) << "Stopping thread " << threads_[i]->getThreadName();
    threads_[i]->stopThread(THREAD_STOP_PERIOD);
  }
}

void Threads::clean() {
  ScopedLock l(lock_);
  for (int i = 0; i < threads_.size(); ++i) {
    if (!threads_[i]->isThreadRunning()) {
      delete threads_[i];
      threads_[i] = threads_.back();
      threads_.pop_back();
    }
  }
}

Thread* Threads::start(InstanceFunction f, const String& name, int wait) {
  return start(makePointer(f, instance_), name, wait);
}

Thread* Threads::start(Callback* cb, const String& name, int wait) {
  clean();

  ptr<Thread> t(thread::makeLoop(wait, name, cb));
  threads_.push_back(t.get());
  t->startThread();
  return t.transfer();
}

}  // namespace slow
}  // namespace rec
