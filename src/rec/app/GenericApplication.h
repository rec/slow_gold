#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"

namespace rec {

template <typename Window>
class GenericApplication : public JUCEApplication {
 public:
  GenericApplication(const String& name, const String& version)
      : name_(name), version_(version) {
  }

  virtual ~GenericApplication() {}

  virtual void initialise(const String& commandLine) {
    window_.reset(new Window());
  }

  virtual void shutdown() {
    window_.reset();
  }

  const String getApplicationName()    { return name_; }
  const String getApplicationVersion() { return version_; }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String& commandLine) {
  }

 protected:
  scoped_ptr<Window> window_;
  const String name_;
  const String version_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
