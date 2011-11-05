#include <gflags/gflags.h>

#include "rec/app/GenericApplication.h"

#include "rec/app/DownloadVersion.h"
#include "rec/app/Files.h"
#include "rec/app/Window.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/data/StartStop.h"
#include "rec/gui/Dialog.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/Undo.h"
#include "rec/data/EditableUpdater.h"

DECLARE_bool(logtostderr);

namespace rec {
namespace app {

GenericApplication::GenericApplication(const String& name, const String& v)
    : name_(name), version_(v) {
}

GenericApplication::~GenericApplication() {}

void GenericApplication::initialise(const String&) {
  FLAGS_logtostderr = true;
  setName(name_);
  if (downloadNewVersionIfNeeded(version_, name_)) {
    quit();
    return;
  }

  audio::format::mpg123::initializeOnce();
  window_.reset(createWindow());
  data::EditableUpdater::instance()->start(window_->getDefaultRegistry());
  window_->initialise();

  thread::runInNewThread("startup thread",
                         STARTUP_THREAD_PRIORITY,
                         window_.get(),
                         &Window::startup);
  LOG(INFO) << name_ << ": initialise finished.";
}

void GenericApplication::shutdown() {
  LOG(INFO) << name_ << ": shutdown starting...";
  enableUndo(false);

  gui::dialog::shutdownDialog();
  window_->shutdown();
  util::thread::trash::waitForAllThreadsToExit(1000);
  data::EditableUpdater::instance()->stop();

  LOG(INFO) << name_ << ": shutdown finished.";
}

}  // namespace app
}  // namespace rec
