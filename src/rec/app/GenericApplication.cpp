#include "rec/app/GenericApplication.h"

#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/app/DownloadVersion.h"

namespace rec {
namespace app {

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

void GenericApplication::initialise(const String&) {
  setApplicationName(name_);
  LOG(INFO) << name_ << ": initialise starting...";
  if (downloadNewVersionIfNeeded(version_, name_)) {
    quit();
    return;
  }

  audio::format::mpg123::initializeOnce();
  persist::AppInstance::start();
  window_.reset(createWindow());
  LOG(INFO) << name_ << ": initialise finished.";
}

void GenericApplication::shutdown() {
  LOG(INFO) << name_ << ": shutdown starting...";

  window_.reset();
  util::thread::trash::waitForAllThreadsToExit(1000);
  persist::AppInstance::stop();
  gui::icon::deleteIcons();

  LOG(INFO) << name_ << ": shutdown finished.";
}

}  // namespace app
}  // namespace rec
