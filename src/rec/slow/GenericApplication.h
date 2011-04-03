#ifndef __REC_JUCE_GENERIC_APPLICATION
#define __REC_JUCE_GENERIC_APPLICATION

#include <string>

#include "rec/data/persist/AppInstance.h"
#include "rec/util/thread/Trash.h"
#include "rec/gui/icon/Icon.h"

namespace rec {
namespace slow {

using juce::RelativeTime;

class GenericApplication : public juce::JUCEApplication {
 public:
  static const int SAVE_PERIOD = 25;
  static const int PRIORITY = 4;

  virtual ~GenericApplication() {}

  GenericApplication(const String& name, const String& version);

  virtual bool initialize();
  virtual void shutdown();

  const String getApplicationName()    { return name_; }
  const String getApplicationVersion() { return version_; }
  bool moreThanOneInstanceAllowed()    { return false; }

  void anotherInstanceStarted (const String&) {}

 protected:
  const String name_;
  const String version_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericApplication);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_JUCE_GENERIC_APPLICATION
