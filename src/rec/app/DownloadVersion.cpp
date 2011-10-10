#include "rec/app/DownloadVersion.h"
#include "rec/app/GenericApplication.h"
#include "rec/app/Files.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace app {

using juce::AlertWindow;
using juce::RelativeTime;
using juce::Time;
using juce::URL;

namespace {

const String WOODSHED("http://www.worldwidewoodshed.com/slowgold/");
const URL VERSION_FILE(WOODSHED + "currentversion/");
const String LAST_UPDATE_FILE("LastUpdate.txt");
const String MUST_UPDATE_FILE("MustUpdate.txt");

// const RelativeTime UPDATE(RelativeTime::days(1));
const RelativeTime UPDATE(1);  // 1 second for testing.

bool isReadyForUpdate() {
  bool ready = true;
  File mustUpdateFile(getAppFile(MUST_UPDATE_FILE));
  if (mustUpdateFile.exists()) {
    LOG(INFO) << "Must-update file exists";

  } else {
    File lastUpdateFile = getAppFile(LAST_UPDATE_FILE);
    if (lastUpdateFile.exists()) {
      Time last = lastUpdateFile.getLastModificationTime();
      Time now = juce::Time::getCurrentTime();
      LOG(INFO) << "now: " << now.toString(true, true);
      LOG(INFO) << "last: " << last.toString(true, true);

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

  return ready;
}

String getVersion() {
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
  return v;
}

bool downloadNewVersion(const String& appName, const String& version) {
  AlertWindow dialog("Downloading a new version " + version,
                     "white", AlertWindow::WarningIcon, NULL);
  dialog.enterModalState();
  bool ok = URL(WOODSHED + appName + "." + version).launchInDefaultBrowser();

  if (!ok) {
    AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                               "Couldn't update to version " + version,
                               "Couldn't update to version " + version,
                               "Click to continue");
  }
  dialog.exitModalState(true);

  return ok;
}

bool checkForNewMajorVersion(const String& current, const String&,
                             String* version) {
  if (!isReadyForUpdate())
    return false;

  (*version) = getVersion();
  if (!version->length()) {
    LOG(ERROR) << "No version file!";
    return false;
  }

  int cmp = majorVersion(*version).compare(majorVersion(current));
  // This cheap comparison won't work if we get a minor version #10 or greater
  // so let's not do that.

  if (cmp < 0)
    LOG(ERROR) << "Future Version number! " << current << ", " << *version;

  return (cmp > 0);
}

}  // namespace

bool downloadNewVersionIfNeeded(const String& version, const String& name) {
  String newVersion;
  bool isNew = checkForNewMajorVersion(version, name, &newVersion);

  if (isNew)
    downloadNewVersion(name, newVersion);
  else
    LOG(INFO) << "No new version needed.  this: "  << version
              << " current: " << newVersion;

  return isNew;
}

}  // namespace app
}  // namespace rec
