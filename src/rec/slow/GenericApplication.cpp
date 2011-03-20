#include "rec/slow/GenericApplication.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace slow {

using persist::getApp;
using juce::URL;
using juce::AlertWindow;

namespace {

const String WOODSHED("http://www.worldwidewoodshed.com/update/");
const URL VERSION_FILE(WOODSHED + "Version.html");
const RelativeTime UPDATE(RelativeTime::days(1));

File getUpdateFile() {
  return getApp()->appDir().getChildFile("LastUpdate.txt");
}

bool isReadyForUpdate() {
  File f = getUpdateFile();
  if (f.exists())
    f.create();

  return (juce::Time::getCurrentTime() - f.getLastModificationTime()) > UPDATE;
}

String getVersion() {
  LOG(INFO) << "update:  " << VERSION_FILE.toString(false).toCString();
  String version = VERSION_FILE.readEntireTextStream();

  if (!(version.length() && version[0] >= '0' && version[0] <= '9'))
    version = "";

  return version;
}

String majorVersion(const String& version) {
  String v(version);

  int i = v.indexOfChar(0, '.');
  if (i >= 0) {
    int j = v.indexOfChar(i + 1, '.');
    if (j >= 0)
      v = v.substring(j + 1);
  }

  return v;
}

bool downloadNewVersion(const String& name, const String& version) {
  AlertWindow dialog("Downloading a new version " + version,
                     "white", AlertWindow::WarningIcon, NULL);
  dialog.enterModalState();
  bool loaded = URL(WOODSHED + name + "." + version).launchInDefaultBrowser();

  if (loaded) {
    getUpdateFile().setLastModificationTime(juce::Time::getCurrentTime());
  } else {
    AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                               "Couldn't update to version " + version,
                               "Couldn't update to version " + version,
                               "Click to continue");
  }
  dialog.exitModalState(true);

  return loaded;
}

bool checkForNewVersions(const String& ver, const String& name) {
  if (!isReadyForUpdate())
    return true;

  String version(getVersion());
  if (!version.length()) {
    LOG(ERROR) << "No version file!";
    return true;
  }

  String major = majorVersion(version);
  int cmp = major.compare(majorVersion(ver));

  if (cmp > 0)
    LOG(ERROR) << "Future Version number! " << ver << ", " << version;

  if (cmp >= 0)
    return true;

  return downloadNewVersion(version, name);
}


}

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}


void GenericApplication::initialise(const String&) {
  persist::AppInstance::start(name_.toCString());
  if (checkForNewVersions(version_, name_)) {
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
