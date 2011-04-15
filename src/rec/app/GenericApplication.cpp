#include "rec/app/GenericApplication.h"

#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/app/ComponentContainer.h"
#include "rec/app/DownloadVersion.h"

namespace rec {
namespace app {

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

void GenericApplication::initialise(const String&) {
  setApplicationName(name_);
  LOG(INFO) << "Initializing " << getApplicationName();
  if (downloadNewVersionIfNeeded(version_, name_)) {
    quit();
    return;
  }

  audio::format::mpg123::initializeOnce();
  persist::AppInstance::start();
  window_.reset(createWindow());

#if TODO
#if JUCE_MAC
  // TODO: make sure this is in the right place.
  juce::MenuBarModel::setMacMainMenu(window_->getTarget());
  window_->setMenuBar(NULL);
#endif
#endif

}

void GenericApplication::shutdown() {
  LOG(INFO) << "Shutting down";

  window_.reset();
  util::thread::trash::waitForAllThreadsToExit(1000);
  persist::AppInstance::stop();
  gui::icon::deleteIcons();

  LOG(INFO) << "Shut down finished.";
}

}  // namespace app
}  // namespace rec
