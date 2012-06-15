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
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/util/Defaulter.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

using namespace juce;

SupportWindow::SupportWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", Colours::azure,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL) {
}

SupportWindow::~SupportWindow() {}

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
}

void SupportWindow::doStartup() {
}

void SupportWindow::doPostStartup() {
}

void SupportWindow::doShutdown() {
}

Component* SupportWindow::getMainComponent() {
  return NULL;
}

MenuBarModel* SupportWindow::getMenuBarModel() {
  return NULL;
}


}  // namespace slow

namespace support {

using namespace rec::data;

void initialize(app::GenericApplication* app) {
  slow::requestSupport();
  app->quit();
}

void shutdown(app::GenericApplication*) {
#ifdef DEBUG
  Trans::dumpAll();
#endif
  data::deleteDataCenter();
}

}  // namespace support
}  // namespace rec
