#ifndef __REC_APP_RECAPPLICATION__
#define __REC_APP_RECAPPLICATION__

#include "rec/base/scoped_ptr.h"

#include "rec/slow/Preferences.h"
#include "rec/app/RecWindow.h"
#include "rec/app/GenericApplication.h"

namespace rec {
namespace app {

class Application : public GenericApplication<RecWindow> {
 public:
  Application() : GenericApplication<RecWindow>("SlowGold", "1.0") {}

  virtual void initialise(const String& commandLine) {
    GenericApplication<RecWindow>::initialise(commandLine);

#if false && JUCE_MAC
    // TODO: fix these casts that Juce seems to require.
    MenuBarModel* model = (MenuBarModel*) window_->getContentComponent();
    MenuBarModel::setMacMainMenu(model);
    window_->setMenuBar(NULL);
#endif
  }

  juce_UseDebuggingNewOperator

 private:
  DISALLOW_COPY_AND_ASSIGN(Application);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_RECAPPLICATION__
