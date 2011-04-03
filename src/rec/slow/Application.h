#ifndef __REC_APP_APPLICATION__
#define __REC_APP_APPLICATION__

#include "rec/slow/GenericApplication.h"
#include "rec/slow/RecWindow.h"
#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace slow {

class Application : public GenericApplication {
 public:
  Application() : GenericApplication("SlowGold", "0.3") {}

  virtual void initialise(const String& commandLine) {
    audio::format::mpg123::initializeOnce();

    if (!GenericApplication::initialize())
      return;

    window_.reset(new RecWindow());

#if JUCE_MAC
    MenuBarModel::setMacMainMenu(window_->getTarget());
    window_->setMenuBar(NULL);
#endif
  }

  virtual void shutdown() {
    window_.reset();
    GenericApplication::shutdown();
  }

 private:
  ptr<RecWindow> window_;
  DISALLOW_COPY_AND_ASSIGN(Application);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_APP_APPLICATION__
