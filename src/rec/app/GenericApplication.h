#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/data/persist/AppInstance.h"
#include "rec/util/thread/Trash.h"
#include "rec/gui/icon/Icon.h"

namespace rec {
namespace app {

class GenericApplication : public juce::JUCEApplication {
 public:
  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;

  virtual ~GenericApplication() {}

  GenericApplication(const String& name, const String& version);

  virtual void initialise(const String& commandLine);
  virtual void shutdown();
  virtual DocumentWindow* createWindow() const = 0;

  virtual const String getApplicationName()    { return name_; }
  virtual const String getApplicationVersion() { return version_; }
  virtual bool moreThanOneInstanceAllowed()    { return false; }
  virtual void anotherInstanceStarted(const String&) {}

 protected:
  const String name_;
  const String version_;
  ptr<DocumentWindow> window_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
