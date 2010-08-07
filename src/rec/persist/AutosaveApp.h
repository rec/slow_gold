#ifndef __REC_PERSIST_AUTOSAVEAPP__
#define __REC_PERSIST_AUTOSAVEAPP__

#include <set>

#include "rec/persist/App.h"
#include "rec/persist/Writeable.h"
#include "juce_amalgamated.h"

namespace rec {
namespace persist {

class AutosaveApp : public App {
 public:
  AutosaveApp(const String& name, int frequency, int priority)
      : thread_("WriteThread " + name, this),
        frequency_(frequency) {
    thread_.startThread(priority);
  }

  const int frequency_;

 private:
  class WriteThread : public Thread {
   public:
    WriteThread(const String& name, AutosaveApp* app)
        : Thread("WriteThread " + name), app_(app) {
    }

    virtual void run() {
      while (!threadShouldExit()) {
        app_->write();
        wait(app_->frequency_);
      }
    }

   private:
    AutosaveApp* app_;
    DISALLOW_COPY_ASSIGN_AND_EMPTY(WriteThread);
  };

  WriteThread thread_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AutosaveApp);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_AUTOSAVEAPP__
