#include "rec/base/scoped_ptr.h"

#include "rec/slow/Preferences.h"
#include "rec/app/RecWindow.h"
#include "rec/app/GenericApplication.h"

namespace rec {

class Application : public GenericApplication<RecWindow> {
 public:
  Application() : GenericApplication<RecWindow>(T("SlowGold"), T("1.0")) {}

  virtual void initialise(const String& commandLine) {
    slow::registerPreferences();
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

}  // namespace rec

START_JUCE_APPLICATION(rec::Application)
