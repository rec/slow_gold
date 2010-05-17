#include "rec/base/scoped_ptr.h"

#include "rec/app/GenericApplication.h"
#include "rec/app/RecWindow.h"

namespace rec {

class Application
  : public rec::GenericApplication<RecWindow> {

 public:
   Application() : rec::GenericApplication<RecWindow>(T("Rec"), T("1.0")) {}
};

}  // namespace rec

START_JUCE_APPLICATION(rec::Application)
