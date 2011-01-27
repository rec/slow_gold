#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/data/persist/AppInstance.h"
#include "rec/util/thread/Trash.h"
#include "rec/gui/icon/Icon.h"

namespace rec {
namespace slow {

class GenericApplication : public juce::JUCEApplication {
 public:

  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;

  GenericApplication(const string& name, const string& version)
      : name_(name), version_(version) {
  }

  virtual ~GenericApplication() {}

  virtual void initialise(const String&) {
    LOG(INFO) << "Starting up " << getApplicationName()
              << ", version " << getApplicationVersion();

    persist::AppInstance::start(name_);
  }

  virtual void shutdown() {
    LOG(INFO) << "Shutting down";
    util::thread::trash::waitForAllThreadsToExit(1000);
    persist::AppInstance::stop();
    // delete juce::MessageManager::getInstance();
    gui::icon::deleteIcons();
    LOG(INFO) << "Shut down finished.";
  }

  const String getApplicationName()    { return name_.c_str(); }
  const String getApplicationVersion() { return version_.c_str(); }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String&) {}

 protected:
  const string name_;
  const string version_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
