#include "rec/app/DownloadVersion.h"
#include "rec/app/AppSettings.pb.h"
#include "rec/app/GenericApplication.h"
#include "rec/app/Files.h"
#include "rec/base/Trans.h"
#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"

TRAN(NEW_VERSION, "A new version of SlowGold, %s, is available.");
TRAN(LIKE_TO_DOWNLOAD, "Would you like to download it?");
TRAN(DOWNLOAD_AND_QUIT, "Download new version and quit this older one.");
TRAN(RUN_THIS_OLDER_VERSION, "Run this older version (%s).");
TRAN(COULDNT_UPDATE, "Couldn't update to version %s");
TRAN(CLICK_TO_CONTINUE, "Click to continue.");

namespace rec {
namespace app {

using juce::AlertWindow;
using juce::RelativeTime;
using juce::Time;
using juce::URL;

using namespace juce;

namespace {

const String WOODSHED("http://www.worldwidewoodshed.com/slowgold/");
const URL VERSION_FILE(WOODSHED + "currentversion/");
const String LAST_UPDATE_FILE("LastUpdate.txt");
const String MUST_UPDATE_FILE("MustUpdate.txt");

// TODO: this is duplicated elsewhere.
const int VERSION_TIMEOUT = 2000;

const RelativeTime UPDATE(RelativeTime::days(1));
// const RelativeTime UPDATE(1);  // 1 second for testing.

bool isReadyForUpdate() {
  CHECK_DDD(1734, 1272, int32, int16);

  int64 finished = data::getProto<AppSettings>().last_update_finished();
  return (juce::Time::currentTimeMillis() - finished) > UPDATE.inMilliseconds();
}

String getVersion() {
  ptr<InputStream> stream(VERSION_FILE.createInputStream(false, NULL, NULL, "",
                                                         VERSION_TIMEOUT));

  return stream->readEntireStreamAsString();
}

class DownloadThread : public Thread {
 public:
  DownloadThread(const String& version, const String& name)
      : Thread("DownloadThread"), version_(version), name_(name) {
  }

  virtual ~DownloadThread() {
    LOG(INFO) << "Deleting " << this;
  }

  virtual void run() {
    checkForUpdates();
  }

  bool checkForUpdates() {
    bool isNew = checkForNewMajorVersion();

    if (!isNew) {
      LOG(INFO) << "Current: "  << version_ << " new: " << newVersion_;
    } else if (downloadNewVersion() && false) {
      LOG(INFO) << "Quitting because we downloaded " << newVersion_;
      JUCEApplication::quit();
      return true;
    }

    return false;
  }

 private:
  bool checkForNewMajorVersion() {
    if (!isReadyForUpdate())
      return false;

    String versionAndOverride = getVersion();
    StringArray vArray;
    vArray.addTokens(versionAndOverride, false);
    if (!vArray.size()) {
      LOG(ERROR) << "No version at all!";
      return false;
    }

    newVersion_ = vArray[0];
    if (!newVersion_.length()) {
      LOG(DFATAL) << "No version file!";
      return false;
    }

    return ((vArray.size() == 1) ? newVersion_ : vArray[1]) > version_;
  }

  bool downloadNewVersion() const {
    String msg = String::formatted(t_NEW_VERSION, c_str(newVersion_));

    LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
    bool ok = AlertWindow::showOkCancelBox(
        AlertWindow::WarningIcon, msg,
        msg + t_LIKE_TO_DOWNLOAD,
        t_DOWNLOAD_AND_QUIT,
        String::formatted(t_RUN_THIS_OLDER_VERSION, c_str(version_)));

    if (!ok) {
      LOG(INFO) << "New version download cancelled";
      return false;
    }

    ok = URL(WOODSHED + name_ + "." + newVersion_).launchInDefaultBrowser();

    if (ok) {
      AppSettings appData = data::getProto<AppSettings>();
      appData.set_last_update_finished(juce::Time::currentTimeMillis());
      data::setProto(appData);
    } else {
      String error = String::formatted(t_COULDNT_UPDATE, c_str(newVersion_));
      AlertWindow::showMessageBox(AlertWindow::WarningIcon, error, error,
                                  t_CLICK_TO_CONTINUE);
    }

    return ok;
  }

  const String version_;
  const String name_;
  String newVersion_;
};

}  // namespace

void downloadNewVersionIfNeeded(const String& version,
                                const String& name) {
  thread::trash::run(new DownloadThread(version, name));
}

bool downloadNewVersionIfNeededBlocking() {
  JUCEApplication* app = JUCEApplication::getInstance();
  const String& version = app->getApplicationVersion();
  const String& name = app->getApplicationName();
  return DownloadThread(version, name).checkForUpdates();
}

}  // namespace app
}  // namespace rec
