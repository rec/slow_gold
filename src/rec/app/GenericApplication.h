#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/app/DownloadVersion.h"
#include "rec/util/Enable.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace app {

class GenericApplication;
class Window;

typedef void (*ApplicationFunction)(GenericApplication* app);

class GenericApplication : public Listener<Enable>,
                           public juce::JUCEApplication {
 public:
  static const int STARTUP_THREAD_PRIORITY = 4;

  GenericApplication(ApplicationFunction initializer,
                     ApplicationFunction shutdown);
  ~GenericApplication() override;

  void initialise(const String& commandLine) override;
  void shutdown() override;
  virtual Window* createWindow() = 0;

  const String getApplicationName() override { return name(); }
  const String getApplicationVersion() override { return version(); }
  bool moreThanOneInstanceAllowed() override { return false; }
  void anotherInstanceStarted(const String& s) override;
  void systemRequestedQuit() override;

  virtual void operator()(Enable enable) {
    Lock l(lock_);
    enable_ = enable;
  }

  const String version() const { return ProjectInfo::versionString; }
  const String name() const { return ProjectInfo::projectName; }
  bool autoCheckForUpdates() const { return autoCheckForUpdates_; }
  void setAutoCheckForUpdates(bool a) { autoCheckForUpdates_ = a; }

 protected:
  ApplicationFunction initializer_;
  ApplicationFunction shutdown_;
  ptr<Window> window_;
  thread_ptr<Thread> startupThread_;
  Enable enable_;
  bool autoCheckForUpdates_;
  CriticalSection lock_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GenericApplication);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
