#include <glog/logging.h>

#include "rec/data/persist/AppInstance.h"
#include "rec/data/persist/Data.h"
#include "rec/util/thread/CallbackLoop.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/STL.h"

namespace rec {
namespace persist {

using namespace rec::util::thread;

AppInstance::AppInstance(const string& appName)
    : App(appName),
      updateThread_(new RunnableThread("App::update",
                               callbackLoop(UPDATE_PERIOD,
                                                    this,
                                                    &AppInstance::update))),
      writeThread_(new RunnableThread("App::write",
                              callbackLoop(WRITE_PERIOD,
                                                   this,
                                                   &AppInstance::write))) {
  CHECK(appName.length());
  updateThread_->setPriority(UPDATE_PRIORITY);
  writeThread_->setPriority(WRITE_PRIORITY);
  updateThread_->startThread();
  writeThread_->startThread();
}

AppInstance::~AppInstance() {
  thread::trash::discard(updateThread_.transfer());
  thread::trash::discard(writeThread_.transfer());
}

// A piece of data got new information!
void AppInstance::needsUpdate(UntypedData* data) {
  {
    ScopedLock l(lock_);
    updateData_.insert(data);
  }
  updateThread_->notify();
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
  if (lockedEmpty(updateData_, &lock_))
    return true;

  DataSet updates;
  extendAndClear(&updateData_, &updates, &lock_);
  for (DataSet::iterator i = updates.begin(); i != updates.end(); ++i)
    (*i)->update();

  extendAndClear(&updates, &writeData_, &lock_);
  writeThread_->notify();
  return true;
}

bool AppInstance::write() {
  if (lockedEmpty(writeData_, &lock_))
    return true;

  DataSet writes;
  extendAndClear(&writeData_, &writes, &lock_);

  for (DataSet::iterator i = writes.begin(); i != writes.end(); ++i)
    (*i)->writeToFile();
  return true;
}

void AppInstance::start(const string& name) {
  CHECK(!instance_);
  instance_ = new AppInstance(name);
}

void AppInstance::stop() {
  CHECK(instance_);
  delete instance_;
  instance_ = NULL;
}

AppInstance* AppInstance::instance_ = NULL;

App* getApp() {
  return AppInstance::getInstance();
}

}  // namespace persist
}  // namespace rec
