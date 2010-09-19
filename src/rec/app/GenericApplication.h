#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"
#include "rec/persist/AppData.h"

namespace rec {

template <typename Window>
class GenericApplication : public JUCEApplication {
 public:
  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;
  GenericApplication(const String& name, const String& version)
      : name_(name), version_(version) {
    rec::persist::createInstance(name, SAVE_PERIOD, PRIORITY);
  }

  virtual ~GenericApplication() {}

  virtual void initialise(const String& commandLine) {
    window_.reset(new Window());
  }

  virtual void shutdown() {
    rec::persist::getInstance()->shutdown();
  }

  const String getApplicationName()    { return name_; }
  const String getApplicationVersion() { return version_; }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String& commandLine) {}

 protected:
  scoped_ptr<Window> window_;
  const String name_;
  const String version_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
