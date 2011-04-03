#include "rec/slow/GenericApplication.h"
#include "rec/slow/DownloadVersion.h"

namespace rec {
namespace slow {

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

bool GenericApplication::initialize() {
  LOG(INFO) << "initialize " << getApplicationName()
            << ", version " << getApplicationVersion();
  String newVersion;
  bool noNewVersion = checkForNewMajorVersion(version_, name_, &newVersion);

  if (noNewVersion) {
    LOG(INFO) << "No new major version";
    persist::AppInstance::start();
  } else {
    downloadNewVersion(name_, newVersion);
    quit();
  }

  return noNewVersion;
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
