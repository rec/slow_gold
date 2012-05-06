#include "rec/app/DownloadVersion.h"
#include "rec/app/GenericApplication.h"
#include "rec/app/Files.h"
#include "rec/base/Trans.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace app {

using juce::AlertWindow;
using juce::RelativeTime;
using juce::Time;
using juce::URL;

using namespace juce;

namespace {

const Trans NEW_VERSION("A new version of SlowGold, %s, is available.");
const Trans LIKE_TO_DOWNLOAD("Would you like to download it?");
const Trans DOWNLOAD_AND_QUIT("Download new version and quit this older one.");
const Trans RUN_THIS_OLDER_VERSION("Run this older version (%s).");
const Trans COULDNT_UPDATE("Couldn't update to version %s");
const Trans CLICK_TO_CONTINUE("Click to continue.");

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
  String msg = String::formatted(NEW_VERSION, c_str(version));

  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  bool ok = AlertWindow::showOkCancelBox(
      AlertWindow::WarningIcon, msg,
      msg + LIKE_TO_DOWNLOAD,
      DOWNLOAD_AND_QUIT,
      String::formatted(RUN_THIS_OLDER_VERSION, c_str(oldVersion)));

  if (!ok) {
    LOG(INFO) << "New version download cancelled";
    return false;
  }

  ok = URL(WOODSHED + appName + "." + version).launchInDefaultBrowser();

  if (!ok) {
    String error = String::formatted(COULDNT_UPDATE, c_str(version));
    AlertWindow::showMessageBox(AlertWindow::WarningIcon, error, error,
                                CLICK_TO_CONTINUE);
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
    DLOG(ERROR) << "Future Version number! " << current << ", " << *version;

  return (cmp > 0);
}

}  // namespace

DownloadStatus downloadNewVersionIfNeeded(const String& version,
                                          const String& name) {
  String newVersion;
  bool isNew = checkForNewMajorVersion(version, name, &newVersion);

  if (!isNew) {
    LOG(INFO) << "New: "  << version << " current: " << newVersion;
    return DOWNLOAD_NOT_FOUND;
  }

  return downloadNewVersion(name, newVersion, version) ? DOWNLOAD_SUCCEEDED :
    DOWNLOAD_CANCELLED_OR_FAILED;
}

void DownloadVersion::translateAll() {
  NEW_VERSION.translate();
  LIKE_TO_DOWNLOAD.translate();
  DOWNLOAD_AND_QUIT.translate();
  RUN_THIS_OLDER_VERSION.translate();
  COULDNT_UPDATE.translate();
  CLICK_TO_CONTINUE.translate();
}

}  // namespace app
}  // namespace rec
