#include "rec/support/SupportWindow.h"

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

SupportWindow::SupportWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", Colours::azure,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL) {
  bool check = data::getGlobal<GuiSettings>().auto_check_for_updates();
  application->setAutoCheckForUpdates(check);
}

SupportWindow::~SupportWindow() {
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

void SupportWindow::init() {
  File appDir = app::getAppDirectory();
  deleteLogs(appDir);
  redirectLogs(appDir);
}

void SupportWindow::constructInstance() {
  instanceDeleter_.reset(new slow::Instance(this));
  instance_ = instanceDeleter_.get();
  instance_->init();
}

void SupportWindow::doStartup() {
  instance_->startup();
}

void SupportWindow::doPostStartup() {
  instance_->postStartup();
}

void SupportWindow::doShutdown() {
  instance_->reset();
  instance_ = NULL;
  instanceDeleter_.reset();
}

void SupportWindow::trashPreferences() {
}

Component* SupportWindow::getMainComponent() {
  return components()->mainPage_->panel();
}

MenuBarModel* SupportWindow::getMenuBarModel() {
  return menus();
}

void SupportWindow::activeWindowStatusChanged() {
}

void SupportWindow::startAboutWindow() {
}

void SupportWindow::stopAboutWindow() {
}

void SupportWindow::minimisationStateChanged(bool isNowMinimised) {
}

}  // namespace slow

namespace support {

using namespace rec::data;

void initialize(app::GenericApplication*) {
  slow::registerProtos();
  slow::translateAll();
}

void shutdown(app::GenericApplication*) {
#ifdef DEBUG
  Trans::dumpAll();
#endif
  data::deleteDataCenter();
}

}  // namespace support
}  // namespace rec
