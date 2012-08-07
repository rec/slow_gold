#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/app/DownloadVersion.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/Listener.h"

namespace rec {
namespace app {

class GenericApplication;
class Window;

typedef void (*ApplicationFunction)(GenericApplication*);

class GenericApplication : public Listener<bool>, public juce::JUCEApplication {
 public:
  static const int STARTUP_THREAD_PRIORITY = 4;

  GenericApplication(ApplicationFunction initializer,
                     ApplicationFunction shutdown);
  virtual ~GenericApplication();

  virtual void initialise(const String& commandLine);
  virtual void shutdown();
  virtual Window* createWindow() = 0;

  virtual const String getApplicationName()    { return name(); }
  virtual const String getApplicationVersion() { return version(); }
  virtual bool moreThanOneInstanceAllowed()    { return false; }
  virtual void anotherInstanceStarted(const String& s);
  virtual void systemRequestedQuit();

  virtual void operator()(bool disabled) { Lock l(lock_); disabled_ = disabled; }

  const String version() const { return ProjectInfo::versionString; }
  const String name() const { return ProjectInfo::projectName; }
  bool autoCheckForUpdates() const { return autoCheckForUpdates_; }
  void setAutoCheckForUpdates(bool a) { autoCheckForUpdates_ = a; }
  DownloadStatus checkForUpdates();

 protected:
  ApplicationFunction initializer_;
  ApplicationFunction shutdown_;
  ptr<Window> window_;
  thread_ptr<Thread> startupThread_;
  bool disabled_;
  bool autoCheckForUpdates_;
  CriticalSection lock_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GenericApplication);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
