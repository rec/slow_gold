#include "rec/app/DownloadVersion.h"
#include "rec/app/AppData.pb.h"
#include "rec/app/GenericApplication.h"
#include "rec/app/Files.h"
#include "rec/base/Trans.h"
#include "rec/data/DataOps.h"
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

const int VERSION_TIMEOUT = 10000000;

const RelativeTime UPDATE(RelativeTime::days(1));
// const RelativeTime UPDATE(1);  // 1 second for testing.

bool isReadyForUpdate() {
  CHECK_DDD(1734, 1272, int32, int16);

  int64 finished = data::getGlobal<AppData>().last_update_finished();
  return (juce::Time::currentTimeMillis() - finished) > UPDATE.inMilliseconds();
}

String getVersion() {
  ptr<InputStream> stream(VERSION_FILE.createInputStream(false, NULL, NULL, "",
                                                         VERSION_TIMEOUT));

  return stream->readEntireStreamAsString();
}

bool downloadNewVersion(const String& appName, const String& version,
                        const String& oldVersion) {
  String msg = String::formatted(NEW_VERSION, c_str(version));

  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
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

  if (ok) {
    AppData appData = data::getGlobal<AppData>();
    appData.set_last_update_finished(juce::Time::currentTimeMillis());
    data::setGlobal(appData);
  } else {
    String error = String::formatted(COULDNT_UPDATE, c_str(version));
    AlertWindow::showMessageBox(AlertWindow::WarningIcon, error, error,
                                CLICK_TO_CONTINUE);
  }

  return ok;
}

bool checkForNewMajorVersion(const String& currentVersion, const String& name,
                             String* version) {
  if (!isReadyForUpdate())
    return false;

  String versionAndOverride = getVersion();
  StringArray vArray;
  vArray.addTokens(versionAndOverride, false);
  if (!vArray.size()) {
    LOG(ERROR) << "No version at all!";
    return false;
  }

  (*version) = vArray[0];
  if (!version->length()) {
    LOG(DFATAL) << "No version file!";
    return false;
  }

  return ((vArray.size() == 1) ? *version : vArray[1]) > currentVersion;
}

}  // namespace

DownloadStatus downloadNewVersionIfNeeded(const String& version,
                                          const String& name) {
  String newVersion;
  bool isNew = checkForNewMajorVersion(version, name, &newVersion);

  if (!isNew) {
    LOG(INFO) << "Current: "  << version << " new: " << newVersion;
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
