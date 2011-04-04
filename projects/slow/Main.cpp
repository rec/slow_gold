#include "rec/slow/GenericApplication.h"
#include "rec/slow/RecWindow.h"
#include "rec/slow/TargetWindow.h"

namespace rec {
namespace slow {
namespace {

class SlowApplication : public Application<RecWindow> {
 public:
  SlowApplication() : Application<RecWindow>("SlowGold", "0.2") {}

  virtual void initialise(const String& commandLine) {
    if (!GenericApplication::initialize())
      return;

  }

 private:
  DISALLOW_COPY_AND_ASSIGN(SlowApplication);
};

}  // namespace
}  // namespace slow
}  // namespace rec

START_JUCE_APPLICATION(rec::slow::SlowApplication)
