#include "rec/slow/Threads.h"
#include "rec/audio/util/FileBuffer.h"
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

static const int PARAMETER_WAIT = 100;
static const int THREAD_STOP_PERIOD = 5000;

void clock(Instance* i) {
  (*i->listeners_)(i->player_->getNextReadPosition());
}

void browser(Instance* i) { i->components_->directoryTree_.checkVolumes(); }

void fetch(Instance* i) {
  Switcher<FileBuffer>* switcher = &i->threads_->data()->fileBuffer_;
  switcher->switchIfNext();
  FileBuffer* buffer = switcher->current();
  if (!buffer || !buffer->buffer_ || buffer->buffer_->isFull())
    Thread::getCurrentThread()->wait(PARAMETER_WAIT);
  else
    buffer->buffer_->fillNextBlock();
}

void persist(Instance* i) {}
void pitch(Instance* i) {}

void updateParameters(Instance* i) {
  Model* model = i->threads_->data();
  model->fileLocker_.broadcastIfChanged(i->listeners_.get());
  model->stretchLocker_.broadcastIfChanged(i->listeners_.get());
  model->loopLocker_.broadcastIfChanged(i->listeners_.get());
}

Threads::Threads(Instance* i) : HasInstance(i), data_(new Model(i)) {}

void Threads::startAll() {
  start(&clock, "Clock", 100);
  start(&browser, "Browser", 1000);
  data_->fetchThread_ = start(&fetch, "Fetch", 10);
  start(&updateParameters, "Parameter", 100);
  start(&persist, "Persist", 100);
  start(&pitch, "Pitch", 100);

  data_->fileLocker_.set(persist::get<VirtualFile>());
}

Threads::~Threads() {
  stop();
  stl::deletePointers(&threads_);
}

void Threads::stop() {
  for (int i = 0; i < threads_.size(); ++i)
    threads_[i]->stopThread(THREAD_STOP_PERIOD);
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
  clean();

  ptr<Callback> cb(makePointer(f, instance_));
  ptr<Thread> t(thread::makeLoop(wait, name, cb.transfer()));

  threads_.push_back(t.get());
  t->startThread();
  return t.transfer();
}

}  // namespace slow
}  // namespace rec
