#include "rec/app/GenericApplication.h"

#include "rec/app/DownloadVersion.h"
#include "rec/app/Files.h"
#include "rec/app/Window.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/data/DataUpdater.h"
#include "rec/gui/Dialog.h"
#include "rec/util/Undo.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace app {

GenericApplication::GenericApplication(const String& n, const String& v,
                                       ApplicationFunction i,
                                       ApplicationFunction s)
    : name_(n), version_(v), initializer_(i), shutdown_(s), disabled_(false) {
}

GenericApplication::~GenericApplication() {}

void GenericApplication::initialise(const String&) {
  FLAGS_logtostderr = true;
#if 0 && JUCE_MAC
  FLAGS_log_dir = str(File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Logs"));
#endif
  setName(name_);
  if (downloadNewVersionIfNeeded(version_, name_)) {
    quit();
    return;
  }

  audio::format::mpg123::initializeOnce();
  initializer_(this);
  window_.reset(createWindow());
  window_->initialise();

  thread::runInNewThread("startup thread",
                         STARTUP_THREAD_PRIORITY,
                         window_.get(),
                         &Window::startup);
  LOG(INFO) << name_ << ": initialise finished.";
}

void GenericApplication::shutdown() {
  LOG(INFO) << name_ << ": shutdown starting...";

  gui::dialog::shutdownDialog();
  window_->shutdown();
  window_.reset();

  util::thread::trash::waitForAllThreadsToExit(1000);
  shutdown_(this);

  LOG(INFO) << name_ << ": shutdown finished.";
}

void GenericApplication::systemRequestedQuit() {
  if (!disabled_)
    JUCEApplication::systemRequestedQuit();
}

}  // namespace app
}  // namespace rec
