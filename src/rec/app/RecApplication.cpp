#include "rec/app/GenericApplication.h"
#include "rec/app/RecWindow.h"
#include "rec/base/scoped_ptr.h"

using rec::juce::GenericApplication;

namespace rec {

class Application
  : public GenericApplication<RecWindow> {

 public:
  Application() : GenericApplication<RecWindow>(T("Rec"), T("1.0")) {}
};

}  // namespace rec

START_JUCE_APPLICATION(rec::Application)
