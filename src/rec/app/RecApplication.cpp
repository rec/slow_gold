#include "rec/base/scoped_ptr.h"

#include "rec/app/GenericApplication.h"
#include "rec/app/RecWindow.h"

namespace rec {

class Application : public rec::GenericApplication<RecWindow> {
 public:
  Application() : rec::GenericApplication<RecWindow>(T("SlowGold"), T("1.0")) {}
  juce_UseDebuggingNewOperator
};

}  // namespace rec

START_JUCE_APPLICATION(rec::Application)
