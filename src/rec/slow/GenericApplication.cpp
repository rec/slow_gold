#include "rec/slow/GenericApplication.h"
#include "rec/data/persist/AppDirectory.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

using persist::getApp;
using juce::URL;
using juce::AlertWindow;
using juce::Time;

namespace {

const String WOODSHED("http://www.worldwidewoodshed.com/slowgold/");
const URL VERSION_FILE(WOODSHED + "currentversion/");
const String LAST_UPDATE_FILE("LastUpdate.txt");
const String MUST_UPDATE_FILE("MustUpdate.txt");

// const RelativeTime UPDATE(RelativeTime::days(1));
const RelativeTime UPDATE(1);  // 1 second for testing.

bool isReadyForUpdate() {
  bool ready = true;
  File mustUpdateFile(getApplicationFile(MUST_UPDATE_FILE));
  if (mustUpdateFile.exists()) {
    LOG(INFO) << "Must-update file exists";

  } else {
    File lastUpdateFile = getApplicationFile(LAST_UPDATE_FILE);
    if (lastUpdateFile.exists()) {
      Time last = lastUpdateFile.getLastModificationTime();
      Time now = juce::Time::getCurrentTime();
      LOG(INFO) << "now: " << now.toString(true, true).toCString();
      LOG(INFO) << "last: " << last.toString(true, true).toCString();

      lastUpdateFile.setLastModificationTime(Time::getCurrentTime());
      ready = (now - last) > UPDATE;

    } else {
      lastUpdateFile.create();
      if (!lastUpdateFile.exists())
        LOG(ERROR) << "Couldn't create lastUpdate file!!";
    }
  }

  if (ready)
    mustUpdateFile.create();
  else
    mustUpdateFile.deleteFile();

  LOG(INFO) << "isReadyForUpdate: " << ready;
  return ready;
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
      v = v.substring(0, j);
  }

  LOG(INFO) << "major: before: " << version 
            << ", after: " << v;
  return v;
}

bool downloadNewVersion(const String& name, const String& version) {
  AlertWindow dialog("Downloading a new version " + version,
                     "white", AlertWindow::WarningIcon, NULL);
  dialog.enterModalState();
  bool loaded = URL(WOODSHED + name + "." + version).launchInDefaultBrowser();

  if (!loaded) {
    AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                               "Couldn't update to version " + version,
                               "Couldn't update to version " + version,
                               "Click to continue");
  }
  dialog.exitModalState(true);

  return loaded;
}

bool checkForNewMajorVersion(const String& current, const String& name,
                             String* version) {
  if (!isReadyForUpdate())
    return true;

  (*version) = getVersion();
  if (!version->length()) {
    LOG(ERROR) << "No version file!";
    return true;
  }

  int cmp = majorVersion(*version).compare(majorVersion(current));
  // This cheap comparison won't work if we get a minor version #10 or greater
  // so let's not do that.

  LOG(INFO) << "cmp: " << cmp;
  if (cmp < 0)
    LOG(ERROR) << "Future Version number! " << current << ", " << *version;

  return (cmp <= 0);
}

}  // namespace

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

bool GenericApplication::initialize() {
  LOG(INFO) << "initialize " << getApplicationName()
            << ", version " << getApplicationVersion();
  String newVersion;
  if (checkForNewMajorVersion(version_, name_, &newVersion)) {
    LOG(INFO) << "No new major version";
    persist::AppInstance::start();
    return true;
  } else {
    downloadNewVersion(name_, newVersion);
    // thread::callAsync(this, &GenericApplication::terminateApp);
    terminateApp();
    return false;
  }
}

void GenericApplication::shutdown() {
  LOG(INFO) << "Shutting down";

  util::thread::trash::waitForAllThreadsToExit(1000);
  persist::AppInstance::stop();
  gui::icon::deleteIcons();
  LOG(INFO) << "Shut down finished.";
}

void GenericApplication::terminateApp() {
  quit();
  // juce::JUCEApplication::appWillTerminateByForce();
}

}  // namespace slow
}  // namespace rec
