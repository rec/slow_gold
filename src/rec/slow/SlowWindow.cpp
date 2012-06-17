#include "rec/slow/SlowWindow.h"

#include "rec/app/Files.h"
#include "rec/app/GenericApplication.h"
#include "rec/data/DataOps.h"
#include "rec/data/DataCenter.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/slow/Components.h"
#include "rec/slow/AboutWindow.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/RegisterProtos.h"
#include "rec/slow/TranslateAll.h"
#include "rec/util/Defaulter.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

namespace {

using namespace juce;

// Skin

const int FADE_IN_TIME = 1500;
const int FADE_OUT_TIME = 750;

}

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", Colours::azure,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL) {
  bool check = data::getGlobal<GuiSettings>().auto_check_for_updates();
  application->setAutoCheckForUpdates(check);
}

SlowWindow::~SlowWindow() {
  aboutWindow_.reset();
}

#define LOG_TO_STDERROR 1

namespace {

void deleteAll(const File& appDir, const String& pattern) {
  DirectoryIterator iterator(appDir, false, pattern);
  while (iterator.next())
    iterator.getFile().deleteFile();
}

void deleteLogs(const File& appDir) {
  deleteAll(appDir, "*.log.*");
  deleteAll(appDir, "il.*");  // TODO: doesn't work.
}

void redirectLogs(const File& appDir) {
#if LOG_TO_STDERROR && JUCE_DEBUG && JUCE_MAC
  FLAGS_logtostderr = true;
#else
  for (google::LogSeverity s = google::INFO; s < google::NUM_SEVERITIES; s++) {
    String logName = String(google::LogSeverityNames[s]) + ".log.";
    string logFile = str(appDir.getChildFile(logName));
    google::SetLogSymlink(s, "");
    google::SetLogDestination(s, logFile.c_str());
  }
#endif
}

}  // namespace

void SlowWindow::init() {
  File appDir = app::getAppDirectory();
  deleteLogs(appDir);
  redirectLogs(appDir);
}

void SlowWindow::constructInstance() {
  instanceDeleter_.reset(new slow::Instance(this));
  instance_ = instanceDeleter_.get();
  instance_->init();
}

void SlowWindow::doStartup() {
  instance_->startup();
}

void SlowWindow::doPostStartup() {
  instance_->postStartup();
}

void SlowWindow::doShutdown() {
  instance_->reset();
  instance_ = NULL;
  instanceDeleter_.reset();
}

void SlowWindow::trashPreferences() {
}

Component* SlowWindow::getMainComponent() {
  return components()->mainPage_->panel();
}

MenuBarModel* SlowWindow::getMenuBarModel() {
  return menus();
}

void SlowWindow::activeWindowStatusChanged() {
  if (menus())
    menus()->menuItemsChanged();
  if (components())
    components()->waveform_->repaint();
}

void SlowWindow::startAboutWindow() {
  if (!aboutWindow_) {
    aboutWindow_.reset(new AboutWindow(getMainComponent(), instance_,
                                       application()->name(),
                                       application()->version()));
  }
  Desktop::getInstance().getAnimator().fadeIn(aboutWindow_.get(), FADE_IN_TIME);
}

void SlowWindow::stopAboutWindow() {
  if (aboutWindow_)
    Desktop::getInstance().getAnimator().fadeOut(aboutWindow_.get(), FADE_OUT_TIME);
}

void SlowWindow::minimisationStateChanged(bool isNowMinimised) {
  if (!isNowMinimised)
    components()->waveform_->repaint();
}

using namespace rec::data;

void initialize(app::GenericApplication*) {
  registerProtos();
  translateAll();
}

void shutdown(app::GenericApplication*) {
#if JUCE_DEBUG && JUCE_MAC
  Trans::dumpAll();
#endif
  data::deleteDataCenter();
}

}  // namespace slow
}  // namespace rec
