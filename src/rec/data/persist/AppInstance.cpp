#include "rec/data/persist/AppInstance.h"
#include "rec/data/persist/Data.h"
#include "rec/util/STL.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace persist {

using data::UntypedEditable;

AppInstance::AppInstance() : App() {
  updateThread_.reset(thread::makeLoop(UPDATE_PERIOD, "App::update",
                                       this, &AppInstance::update));
  updateThread_->setPriority(UPDATE_PRIORITY);

  writeThread_.reset(thread::makeLoop(WRITE_PERIOD, "App::write",
                                       this, &AppInstance::write));
  writeThread_->setPriority(WRITE_PRIORITY);
  updateThread_->startThread();
  writeThread_->startThread();
}

AppInstance::~AppInstance() {
  writeThread_->stopThread(1000);
  updateThread_->stopThread(1000);
}

// A piece of data got new information!
void AppInstance::needsUpdate(UntypedEditable* data) {
  {
    ScopedLock l(lock_);
    updateData_.insert(data);
  }
  updateThread_->notify();
}

bool AppInstance::running() const {
	return writeThread_ && updateThread_ &&
    !(writeThread_->threadShouldExit() || writeThread_->threadShouldExit());
}

template <typename Container>
bool lockedEmpty(const Container &c, CriticalSection* lock) {
  ScopedLock l(*lock);
  return c.empty();
}

template <typename Container>
void extendAndClear(Container *from, Container *to, CriticalSection* lock) {
  ScopedLock l(*lock);
  if (to->empty()) {
    to->swap(*from);
  } else {
    to->insert(from->begin(), from->end());
    to->clear();
  }
}

bool AppInstance::update() {
  if (lockedEmpty(updateData_, &lock_) || !running())
    return true;

  DataSet updates;
  extendAndClear(&updateData_, &updates, &lock_);
  for (DataSet::iterator i = updates.begin(); i != updates.end() && running(); ++i)
    (*i)->update();

  extendAndClear(&updates, &writeData_, &lock_);
  if (running())
    writeThread_->notify();
  return true;
}

bool AppInstance::write() {
  if (lockedEmpty(writeData_, &lock_))
    return true;

  DataSet writes;
  extendAndClear(&writeData_, &writes, &lock_);

  for (DataSet::iterator i = writes.begin(); i != writes.end() && running(); ++i)
    (*i)->writeToFile();
  return true;
}

void AppInstance::start() {
  CHECK(!instance_);
  instance_ = new AppInstance();
}

void AppInstance::stop() {
  delete instance_;
  instance_ = NULL;
}

AppInstance* AppInstance::instance_ = NULL;

App* getApp() {
  return AppInstance::getInstance();
}

}  // namespace persist
}  // namespace rec
