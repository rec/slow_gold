#include "rec/persist/AppInstance.h"
#include "rec/thread/CallbackLoop.h"

namespace rec {
namespace persist {

AppInstance::AppInstance(const std::string& appName)
    : App(appName),
      updateThread_("App::update",
                    thread::callbackLoop(UPDATE_PERIOD, this, &AppInstance::update)),
      writeThread_("App::write",
                   thread::callbackLoop(WRITE_PERIOD, this, &AppInstance::write)) {
  CHECK(appName.length());
  appDir_.createDirectory();

  updateThread_.setPriority(UPDATE_PRIORITY);
  writeThread_.setPriority(WRITE_PRIORITY);

  updateThread_.startThread();
  writeThread_.startThread();
}

AppInstance::~AppInstance() {
  updateThread_.stopThread(1000);
  writeThread_.stopThread(1000);
}

// A piece of data got new information!
void AppInstance::needsUpdate(UntypedData* data) {
  {
    ScopedLock l(lock_);
    updateData_.insert(data);
  }
  updateThread_.notify();
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

void AppInstance::update() {
  if (lockedEmpty(updateData_, &lock_))
    return;

  DataSet updates;
  extendAndClear(&updateData_, &updates, &lock_);
  for (DataSet::iterator i = updates.begin(); i != updates.end(); ++i)
    (*i)->update();

  extendAndClear(&updates, &writeData_, &lock_);
  writeThread_.notify();
}

void AppInstance::write() {
  if (lockedEmpty(writeData_, &lock_))
    return;

  DataSet writes;
  extendAndClear(&writeData_, &writes, &lock_);

  for (DataSet::iterator i = writes.begin(); i != writes.end(); ++i)
    (*i)->writeToFile();
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
