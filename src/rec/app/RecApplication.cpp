#include "rec/base/scoped_ptr.h"

#include "rec/app/RecWindow.h"
#include "rec/persist/AppData.h"
#include "rec/app/GenericApplication.h"

namespace rec {

class Application : public GenericApplication<RecWindow> {
 public:
  Application() : rec::GenericApplication<RecWindow>(T("SlowGold"), T("1.0")) {
    rec::persist::createInstance(getApplicationName(), 1000, 4);
  }

#if false && JUCE_MAC
  virtual void initialise(const String& commandLine) {
    GenericApplication<RecWindow>::initialise(commandLine);

    // TODO: fix these casts that Juce seems to require.
    MenuBarModel* model = (MenuBarModel*) window_->getContentComponent();
    MenuBarModel::setMacMainMenu(model);
    window_->setMenuBar(NULL);
  }
#endif

  juce_UseDebuggingNewOperator

 private:
  DISALLOW_COPY_AND_ASSIGN(Application);
};

}  // namespace rec

START_JUCE_APPLICATION(rec::Application)
