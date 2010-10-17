#ifndef __REC_APP_RECAPPLICATION__
#define __REC_APP_RECAPPLICATION__

#include "rec/slow/app/GenericApplication.h"
#include "rec/slow/app/RecWindow.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace app {

class Application : public GenericApplication {
 public:
  Application() : GenericApplication("SlowGold", "1.0") {}

  virtual void initialise(const String& commandLine) {
    GenericApplication::initialise(commandLine);
    window_.reset(new RecWindow());

#if 0 && JUCE_MAC
    // TODO: fix these casts that Juce seems to require.
    MenuBarModel* model = (MenuBarModel*) window_->getContentComponent();
    MenuBarModel::setMacMainMenu(model);
    window_->setMenuBar(NULL);
#endif
  }

  juce_UseDebuggingNewOperator

 private:
  scoped_ptr<RecWindow> window_;
  DISALLOW_COPY_AND_ASSIGN(Application);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_RECAPPLICATION__
