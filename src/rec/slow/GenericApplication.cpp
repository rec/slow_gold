#include "rec/slow/GenericApplication.h"
#include "rec/slow/DownloadVersion.h"

namespace rec {
namespace slow {

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

bool GenericApplication::initialize() {
  LOG(INFO) << "Initializing " << getApplicationName();
  bool downloaded = downloadNewVersionIfNeeded(version_, name_);
  if (downloaded)
    quit();
  else
    persist::AppInstance::start();

  return !downloaded;
}

void GenericApplication::shutdown() {
  LOG(INFO) << "Shutting down";

  util::thread::trash::waitForAllThreadsToExit(1000);
  persist::AppInstance::stop();
  gui::icon::deleteIcons();

  LOG(INFO) << "Shut down finished.";
}

}  // namespace slow
}  // namespace rec
