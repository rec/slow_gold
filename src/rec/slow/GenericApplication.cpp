#include "rec/slow/GenericApplication.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace slow {

using persist::getApp;
using juce::URL;
using juce::AlertWindow;

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

String GenericApplication::majorVersion(const String& version) {
  String v(version);

  int i = v.indexOfChar(0, '.');
  if (i >= 0) {
    int j = v.indexOfChar(i + 1, '.');
    if (j >= 0)
      v = v.substring(j + 1);
  }

  return v;
}

bool GenericApplication::checkForNewVersions() {
  File f = getApp()->appDir().getChildFile("LastUpdate.txt");
  if (f.exists())
    f.create();

  static const String WOODSHED("http://www.worldwidewoodshed.com/update/");
  static const URL VERSION_FILE(WOODSHED + "Version.html");
  static const RelativeTime UPDATE(RelativeTime::days(1));

  if ((juce::Time::getCurrentTime() - f.getLastModificationTime()) < UPDATE)
    return true;

  LOG(INFO) << "update:  " << VERSION_FILE.toString(false).toCString();
  String version = VERSION_FILE.readEntireTextStream();

  if (!(version.length() && version[0] >= '0' && version[0] <= '9'))
    version = "";

  if (!version.length()) {
    LOG(ERROR) << "No version file!";
    return true;
  }

  String major = majorVersion(version);
  int cmp = majorVersion(version).compare(majorVersion(version_));

  if (cmp > 0)
    LOG(ERROR) << "Future Version number! " << version_ << ", " << major;

  if (cmp >= 0)
    return true;

  AlertWindow dialog("Downloading a new version " + version,
                     "white", AlertWindow::WarningIcon, NULL);
  dialog.enterModalState();
  bool ok = URL(WOODSHED + name_ + "." + version).launchInDefaultBrowser();
  if (ok) {
    f.setLastModificationTime(juce::Time::getCurrentTime());
  } else {
    AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                               "Couldn't update to version " + version,
                               "Couldn't update to version " + version,
                               "Click to continue");
  }
  dialog.exitModalState(true);

  return ok;
}

void GenericApplication::initialise(const String&) {
  persist::AppInstance::start(name_.toCString());
  if (checkForNewVersions()) {
    LOG(INFO) << "Starting up " << getApplicationName()
              << ", version " << getApplicationVersion();
  } else {
    LOG(INFO) << "Downloading new version for " << getApplicationName()
              << ", version " << getApplicationVersion();
    shutdown();
  }
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
