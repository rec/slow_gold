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

const bool UPDATE_ON_MINOR_VERSION_CHANGE = true;

const RelativeTime UPDATE(RelativeTime::days(1));
// const RelativeTime UPDATE(1);  // 1 second for testing.

bool isReadyForUpdate() {
  CHECK_DDD(1734, 1272, int32, int16);

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
        LOG(DFATAL) << "Couldn't create lastUpdate file!!";
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

bool downloadNewVersion(const String& appName, const String& version,
                        const String& oldVersion) {
  String msg = String::formatted(
      translate("A new version of SlowGold, %s is available."), c_str(version));
  bool ok = AlertWindow::showOkCancelBox(
      AlertWindow::WarningIcon, msg,
      msg + translate("Would you like to download it?"),
      translate("Download new version and quit this old one."),
      String::formatted(translate("Run this old version %s."),
                        c_str(oldVersion)));

  if (!ok) {
    LOG(INFO) << "New version download cancelled";
    return false;
  }

  ok = URL(WOODSHED + appName + "." + version).launchInDefaultBrowser();

  if (!ok) {
    String error = String::formatted(translate("Couldn't update to version %s"),
                                     c_str(version));
    AlertWindow::showMessageBox(AlertWindow::WarningIcon, error, error,
                                translate("Click to continue"));
  }
  return ok;
}

bool checkForNewMajorVersion(const String& current, const String&,
                             String* version) {
  if (!isReadyForUpdate())
    return false;

  (*version) = getVersion();
  if (!version->length()) {
    LOG(DFATAL) << "No version file!";
    return false;
  }

  int cmp = UPDATE_ON_MINOR_VERSION_CHANGE ?
    version->compare(current) :
    majorVersion(*version).compare(majorVersion(current));
  // This cheap comparison won't work if we get a minor version #10 or greater
  // so let's not do that. :-D

  if (cmp < 0)
    LOG(DFATAL) << "Future Version number! " << current << ", " << *version;

  return (cmp > 0);
}

}  // namespace

bool downloadNewVersionIfNeeded(const String& version, const String& name) {
  String newVersion;
  bool isNew = checkForNewMajorVersion(version, name, &newVersion);

  if (!isNew)
    LOG(INFO) << "New: "  << version << " current: " << newVersion;

  return isNew && downloadNewVersion(name, newVersion, version);
}

}  // namespace app
}  // namespace rec
