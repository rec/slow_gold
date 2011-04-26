#include "rec/slow/Threads.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/Locker.h"
#include "rec/util/STL.h"

namespace rec {
namespace slow {

using namespace rec::audio::stretch;
using namespace rec::util::thread;

static const int PARAMETER_WAIT = 100;

struct ParameterUpdater {
  ParameterUpdater() : fileLocker_(&lock_), stretchLocker_(&lock_) {}

  Locker<VirtualFile> fileLocker_;
  Locker<StretchLoop> stretchLocker_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(ParameterUpdater);
};


struct ThreadData {
  ParameterUpdater updater_;
};

static const int THREAD_STOP_PERIOD = 5000;

void clock(Instance* i) { (*i->listeners_)(i->player_->getNextReadPosition()); }
void browser(Instance* i) { i->components_->directoryTree_.checkVolumes(); }
void fetch(Instance* i) {}

void setVirtualFile(Instance* i, const VirtualFile& f, const StretchLoop& s) {

}

void setStretch(Instance* i, const VirtualFile& f, const StretchLoop& s) {

}


void parameter(Instance* i) {
  ParameterUpdater* updater = &i->threads_->data()->updater_;
  VirtualFile file;
  if (updater->fileLocker_.readAndClearChanged(&file)) {
    StretchLoop loop = persist::get<StretchLoop>(file);
    updater->stretchLocker_.initialize(loop);
    setVirtualFile(i, file, loop);
  } else {
    StretchLoop stretch;
    if (updater->stretchLocker_.readAndClearChanged(&stretch))
      setStretch(i, file, stretch);
  }
}

void persist(Instance* i) {}
void pitch(Instance* i) {}

Threads::Threads(Instance* i) : instance_(i), threadData_(new ThreadData()) {}

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
