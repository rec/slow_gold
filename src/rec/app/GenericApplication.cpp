#include <gflags/gflags.h>

#include "rec/app/GenericApplication.h"

#include "rec/app/DownloadVersion.h"
#include "rec/app/Files.h"
#include "rec/app/Window.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/data/persist/EditableFactory.h"
#include "rec/gui/Dialog.h"
#include "rec/util/thread/Trash.h"

DECLARE_bool(logtostderr);

namespace rec {
namespace app {

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

void GenericApplication::initialise(const String&) {
  FLAGS_logtostderr = true;
  setName(name_);
  LOG(INFO) << name_ << ": initialise starting...";
  if (downloadNewVersionIfNeeded(version_, name_)) {
    quit();
    return;
  }

  audio::format::mpg123::initializeOnce();
  data::start();
  window_.reset(createWindow());
  window_->initialise();
  LOG(INFO) << name_ << ": initialise finished.";
}

void GenericApplication::shutdown() {
  LOG(INFO) << name_ << ": shutdown starting...";

  gui::dialog::shutdownDialog();
  window_->shutdown();
  util::thread::trash::waitForAllThreadsToExit(1000);
  data::stop();

  LOG(INFO) << name_ << ": shutdown finished.";
}

}  // namespace app
}  // namespace rec
