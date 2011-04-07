#include "rec/slow/GenericApplication.h"

#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/slow/ComponentContainer.h"
#include "rec/slow/DownloadVersion.h"

namespace rec {
namespace slow {

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

#if JUCE_MAC
  juce::MenuBarModel::setMacMainMenu(window_->getTarget());
  window_->setMenuBar(NULL);
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

}  // namespace slow
}  // namespace rec
