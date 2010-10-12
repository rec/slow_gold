#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>
#include <glog/logging.h>

#include "rec/data/persist/AppInstance.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {

class GenericApplication : public juce::JUCEApplication {
 public:

  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;

  GenericApplication(const string& name, const string& version)
      : name_(name), version_(version) {
  }

  virtual ~GenericApplication() {}

  virtual void initialise(const String& commandLine) {
    LOG(INFO) << "Starting up " << getApplicationName()
              << ", version " << getApplicationVersion();
    persist::AppInstance::start(name_);
  }

  virtual void shutdown() {
    persist::AppInstance::stop();
    LOG(INFO) << "Shutting down " << getApplicationName();
  }

  const String getApplicationName()    { return name_.c_str(); }
  const String getApplicationVersion() { return version_.c_str(); }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String& commandLine) {}

 protected:
  const string name_;
  const string version_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
