#include "rec/persist/App.h"

namespace rec {
namespace persist {

using rec::persist::AppBase::DataSet;

App::App(const String& appName)
    : AppBase(appName),
      updateThread_("App::update",
                    thread::callbackLoop(UPDATE_PERIOD, &App::update)),
      writeThread_("App::write",
                   thread::callbackLoop(WRITE_PERIOD, &App::write)) {
  CHECK(appName.length());
  appDir().createDirectory();

  updateThread_.setPriority(UPDATE_PRIORITY);
  writeThread_.setPriority(WRITE_PRIORITY);

  updateThread_.startThread();
  writeThread_.startThread();
}

App::~App() {
  updateThread_.stopThread();
  writeThread_.stopThread();
  stl::deleteMapPointers(&dataSet_);
}

// A piece of data got new information!
void App::needsUpdate(Data* data) {
  {
    ScopedLock l(lock_);
    updateData_.push_back(data);
  }
  updateThread_.notify();
}

// This method allows update() and write() to be efficiently thread-safe.
static void swap(DataSet* l1, DataSet* l2, CriticalSection* lock) {
  ScopedLock l(*lock);
  l1->swap(*l2);
}

void App::update() {
  DataSet updates;
  swap(&updates, &updateData_, &lock_);

  for (DataSet::iterator i = updates.begin(); i != updates.end(); ++i)
    i->update();

  swap(&updates, &writeData_, &lock_);
  writeThread_.notify();
}

void App::write() {
  DataSet writes;
  swap(&writes, &writeData_, &lock_);

  for (DataSet::iterator i = updates.begin(); i != updates.end(); ++i)
    i->write();
}

void App::start(const String& name) {
  CHECK(!instance_);
  instance_ = new App(name);
}

void App::stop() {
  CHECK(instance_);
  delete instance_;
  instance_ = NULL;
}

AppBase* App::instance_ = NULL;

AppBase* getApp() {
  return App::instance_;
}

}  // namespace persist
}  // namespace rec
