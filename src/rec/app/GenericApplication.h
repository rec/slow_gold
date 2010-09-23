#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"
#include "rec/persist/App.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {

template <typename Window>
class GenericApplication : public JUCEApplication {
 public:
  typedef std::string string;
  
  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;
  GenericApplication(const string& name, const string& version)
      : name_(name), version_(version) {
  }

  virtual ~GenericApplication() {}

  virtual void initialise(const String& commandLine) {
    persist::App::start(name_);
    window_.reset(new Window());
  }

  virtual void shutdown() {
    persist::App::stop();
  }

  const String getApplicationName()    { return name_.c_str(); }
  const String getApplicationVersion() { return version_.c_str(); }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String& commandLine) {}

 protected:
  scoped_ptr<Window> window_;
  const string name_;
  const string version_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
