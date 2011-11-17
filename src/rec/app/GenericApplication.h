#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/util/thread/Trash.h"
#include "rec/util/Listener.h"

namespace rec {

namespace util { class DefaultRegistry; }

namespace app {

class Window;

class GenericApplication : public Listener<bool>, public juce::JUCEApplication {
 public:
  static const int STARTUP_THREAD_PRIORITY = 4;

  GenericApplication(const String& name, const String& version);
  virtual ~GenericApplication();

  virtual void initialise(const String& commandLine);
  virtual void shutdown();
  virtual Window* createWindow() = 0;

  virtual const String getApplicationName()    { return name_; }
  virtual const String getApplicationVersion() { return version_; }
  virtual bool moreThanOneInstanceAllowed()    { return false; }
  virtual void anotherInstanceStarted(const String&) {}
  virtual void systemRequestedQuit();

  virtual void operator()(bool disabled) { Lock l(lock_); disabled_ = disabled; }

 protected:
  virtual void registerDefaults(DefaultRegistry*) {}

  CriticalSection lock_;
  const String name_;
  const String version_;
  ptr<Window> window_;
  thread_ptr<Thread> startupThread_;
  bool disabled_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
