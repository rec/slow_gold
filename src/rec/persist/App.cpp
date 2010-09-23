#include "rec/persist/App.h"
#include "rec/thread/CallbackLoop.h"

namespace rec {
namespace persist {

App::App(const std::string& appName)
    : AppBase(appName),
      updateThread_("App::update",
                    thread::callbackLoop(UPDATE_PERIOD, this, &App::update)),
      writeThread_("App::write",
                   thread::callbackLoop(WRITE_PERIOD, this, &App::write)) {
  CHECK(appName.length());
  appDir_.createDirectory();

  updateThread_.setPriority(UPDATE_PRIORITY);
  writeThread_.setPriority(WRITE_PRIORITY);

  updateThread_.startThread();
  writeThread_.startThread();
}

App::~App() {
  updateThread_.stopThread(1000);
  writeThread_.stopThread(1000);
}

// A piece of data got new information!
void App::needsUpdate(UntypedData* data) {
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

void App::update() {
  if (lockedEmpty(updateData_, &lock_))
    return;

  DataSet updates;
  extendAndClear(&updateData_, &updates, &lock_);
  for (DataSet::iterator i = updates.begin(); i != updates.end(); ++i)
    (*i)->update();

  extendAndClear(&updates, &writeData_, &lock_);
  writeThread_.notify();
}

void App::write() {
  if (lockedEmpty(writeData_, &lock_))
    return;

  DataSet writes;
  extendAndClear(&writeData_, &writes, &lock_);

  for (DataSet::iterator i = writes.begin(); i != writes.end(); ++i)
    (*i)->writeToFile();
}

void App::start(const string& name) {
  CHECK(!instance_);
  instance_ = new App(name);
}

void App::stop() {
  CHECK(instance_);
  delete instance_;
  instance_ = NULL;
}

App* App::instance_ = NULL;

AppBase* getApp() {
  return App::getInstance();
}

}  // namespace persist
}  // namespace rec
