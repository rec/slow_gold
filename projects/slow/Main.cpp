#include "rec/slow/GenericApplication.h"
#include "rec/slow/TargetWindow.h"
#include "rec/slow/RecWindow.h"
#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace slow {
namespace {

class Application : public GenericApplication {
 public:
  Application() : GenericApplication("SlowGold", "0.2") {}

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
  ptr<TargetWindow> window_;
  DISALLOW_COPY_AND_ASSIGN(Application);
};

}  // namespace
}  // namespace slow
}  // namespace rec

START_JUCE_APPLICATION(rec::slow::Application)
