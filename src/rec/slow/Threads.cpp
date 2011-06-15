#include "rec/slow/Threads.h"
#include "rec/data/persist/Persist.h"
#include "rec/audio/source/Buffered.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Threads.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/Directory.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;
using namespace rec::util::thread;

static const int THREAD_STOP_PERIOD = 5000;
static const int BUFFER_FILL_CHUNK = Buffered::BUFFER_SIZE / 2;

Threads::Threads(Instance* i) : HasInstance(i),
                                fetchThread_(NULL), bufferThread_(NULL) {}

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

namespace {

void navigator(Instance* i) {
  i->components_->directoryTree_.checkVolumes();
}

void fetch(Instance* i) {
  i->model_->fillOnce();
}

void updateParameters(Instance* i) {
  i->model_->checkChanged();
}

void buffer(Instance* i) {
  while (i->player_->buffered()->fillBuffer(BUFFER_FILL_CHUNK))
    Thread::yield();
}

void directory(Instance* i) {
  while (i->components_->directoryTree_.run())
    Thread::yield();
}

static Component* lastComp = NULL;
void focus(Instance*) {
  Component* c = Component::getCurrentlyFocusedComponent();
  if (c != lastComp)
    lastComp = c;
}

}  // namespace

void Threads::startAll() {
  start(&navigator, "Navigator", 1000);
	fetchThread_ = start(&fetch, "Fetch", 10);
  start(&updateParameters, "Parameter", 97);
  player()->buffered()->setNotifyThread(start(&buffer, "Buffer", 10));
  start(&directory, "Directory", 101);
  // start(&focus, "Focus", 10);
  // start(&pitch, "Pitch", 100);

  (*model()->fileLocker())(persist::get<VirtualFile>());
}

}  // namespace slow
}  // namespace rec
