#ifndef __REC_PERSIST_AUTOSAVEAPP__
#define __REC_PERSIST_AUTOSAVEAPP__

#include <set>

#include "rec/event/EventQueue.h"
#include "rec/persist/App.h"
#include "rec/persist/Writeable.h"
#include "rec/thread/CallbackLoop.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

class AutosaveApp : public App {
 public:
  AutosaveApp(const String& name, int period, int priority)
      : App(name),
        thread_("WriteThread " + name,
                thread::callbackLoop(period, this, &AutosaveApp::write)),
        events_(new event::EventQueue(getDataFile("events.log", "Event"))) {
    CHECK(name.length() > 0);
    thread_.startThread(priority);
  }

  ~AutosaveApp() { shutdown(); }

  void addEvent(event::Event* event) {
    ScopedLock l(lock_);
    events_->add(event);
  }

  void write() {
    ScopedLock l(lock_);
    App::write();
    events_->write();
  }

  // Temporary, see https://github.com/rec/rec/issues/issue/40
  virtual void shutdown() {
    thread_.stopThread(100);
    write();
  }

 private:
  thread::RunnableThread thread_;
  scoped_ptr<event::EventQueue> events_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AutosaveApp);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_AUTOSAVEAPP__
