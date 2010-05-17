#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include "juce_amalgamated.h"
#include "rec/base/scoped_ptr.h"

namespace rec {

template <typename Window>
class GenericApplication : public JUCEApplication {
 private:
  scoped_ptr<Window> window_;
  const String name_;
  const String version_;


 public:
  GenericApplication(const String& name, const String& version)
      : name_(name), version_(version) {
  }
  ~GenericApplication() {}

  void initialise(const String& commandLine) {
    window_.reset(new Window());
  }

  void shutdown() {
    window_.reset();
  }

  const String getApplicationName()    { return name_; }
  const String getApplicationVersion() { return version_; }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String& commandLine) {
  }
};

}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
