#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/util/thread/Trash.h"

namespace rec {

namespace util { class DefaultRegistry; }

namespace app {

class Window;

class GenericApplication : public juce::JUCEApplication {
 public:
  static const int STARTUP_THREAD_PRIORITY = 4;

  virtual ~GenericApplication();

  GenericApplication(const String& name, const String& version);

  virtual void initialise(const String& commandLine);
  virtual void shutdown();
  virtual Window* createWindow() const = 0;

  virtual const String getApplicationName()    { return name_; }
  virtual const String getApplicationVersion() { return version_; }
  virtual bool moreThanOneInstanceAllowed()    { return false; }
  virtual void anotherInstanceStarted(const String&) {}

 protected:
  virtual void registerDefaults(DefaultRegistry*) {}

  const String name_;
  const String version_;
  ptr<Window> window_;
  thread_ptr<Thread> startupThread_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
