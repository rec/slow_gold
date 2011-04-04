#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/data/persist/AppInstance.h"
#include "rec/util/thread/Trash.h"
#include "rec/gui/icon/Icon.h"
#include "rec/slow/TargetWindow.h"

namespace rec {
namespace slow {

class GenericApplication : public juce::JUCEApplication {
 public:
  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;

  virtual ~GenericApplication() {}

  GenericApplication(const String& name, const String& version);

  virtual bool initialize();
  virtual void shutdown();
  virtual TargetWindow* createWindow() const { return NULL; }  // = 0;

  const String getApplicationName()    { return name_; }
  const String getApplicationVersion() { return version_; }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String&) {}

 protected:
  const String name_;
  const String version_;
  ptr<TargetWindow> window_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

#if 0
template <typename Window>
class Application : public GenericApplication {
 public:
  Application(const String& n, const String& v) : GenericApplication(n, v) {}
  virtual TargetWindow* createWindow() const { return new Window; }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Application);
};
#endif

}  // namespace slow
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
