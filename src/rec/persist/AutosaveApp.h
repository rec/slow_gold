#ifndef __REC_PERSIST_AUTOSAVEAPP__
#define __REC_PERSIST_AUTOSAVEAPP__

#include <set>

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
                thread::callbackLoop(period, this, &AutosaveApp::write)) {
    CHECK(name.length() > 0);
    thread_.startThread(priority);
  }

 private:
  thread::RunnableThread thread_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AutosaveApp);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_AUTOSAVEAPP__
