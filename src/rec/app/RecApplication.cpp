#include "rec/base/scoped_ptr.h"

#include "rec/app/GenericApplication.h"
#include "rec/app/RecWindow.h"
#include "rec/persist/AppData.h"

namespace rec {

class Application : public rec::GenericApplication<RecWindow> {
 public:
  Application() : rec::GenericApplication<RecWindow>(T("SlowGold"), T("1.0")) {
    rec::persist::createInstance(getApplicationName(), 1000, 4);
  }

  juce_UseDebuggingNewOperator

 private:
  DISALLOW_COPY_AND_ASSIGN(Application);
};

}  // namespace rec

START_JUCE_APPLICATION(rec::Application)
