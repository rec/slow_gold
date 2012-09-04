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
#include "rec/slow/LegacyDatabase.pb.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/RegisterProtos.h"
#include "rec/slow/RegisterAllTranslations.h"
#include "rec/util/proto/Defaulter.h"
#include "rec/util/proto/ReadProtoFile.h"
#include "rec/util/file/FileType.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

namespace {

#define LOG_TO_STDERROR 1

using namespace juce;

const int FADE_IN_TIME = 1500;
const int FADE_OUT_TIME = 750;

const char WOODSHED_SUFFIX[] = "wshed";

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

}

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", Colours::azure,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL),
      startupFinished_(false) {
  bool check = data::getProto<GuiSettings>().auto_check_for_updates();
  application->setAutoCheckForUpdates(check);
}

SlowWindow::~SlowWindow() {
  aboutWindow_.reset();
}


void SlowWindow::init() {
  File appDir = app::getAppDirectory();
  deleteLogs(appDir);
  redirectLogs(appDir);
}

void SlowWindow::constructInstance() {
  doLog("in constructInstance");
  instanceDeleter_.reset(new slow::Instance(this));
  doLog("instance constructed");
  instance_ = instanceDeleter_.get();
  doLog("initializing instance");
  instance_->init();
}

void SlowWindow::doStartup() {
  instance_->startup();
}

void SlowWindow::gotoNextFile() {
  if (nextFile_ != File::nonexistent) {
    if (nextFile_.hasFileExtension(WOODSHED_SUFFIX)) {
      const MessageMaker& maker = data::getDataCenter().getMessageMaker();
      ptr<Message> msg(readProtoFile(nextFile_, maker));
      if (!msg)
        LOG(DFATAL) << "Couldn't read woodshed file " << str(nextFile_);
      else if (const LegacyDatabase* db = dynamic_cast<LegacyDatabase*>(msg.get()))
        data::setProto(*db, data::global());
      else
        LOG(DFATAL) << "Database type" << getTypeName(*msg);
    } else {
      currentFile()->setFile(nextFile_);
    }
  }
}

void SlowWindow::doPostStartup() {
  Lock l(lock_);

  instance_->postStartup();
  startupFinished_ = true;
  gotoNextFile();
}

void SlowWindow::doShutdown() {
  instance_->reset();
  instance_ = NULL;
  instanceDeleter_.reset();
}

void SlowWindow::anotherInstanceStarted(const String& f) {
  Lock l(lock_);

  nextFile_ = File(f.trimCharactersAtEnd("\"").
                   trimCharactersAtStart("\""));
  if (startupFinished_)
    gotoNextFile();
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
  if (aboutWindow_) {
    Desktop::getInstance().getAnimator().fadeOut(aboutWindow_.get(),
                                                 FADE_OUT_TIME);
  }
}

void SlowWindow::minimisationStateChanged(bool isNowMinimised) {
  if (!isNowMinimised)
    components()->waveform_->repaint();
}

using namespace rec::data;

void initialize(app::GenericApplication*) {
  doLog("in initialize");
  // LOG(INFO) << "SlowWindow::initialize";
  // TODO:  logging doesn't work if called in this routine...
  doLog("moving directories");
  file::moveOldAbsoluteDirectoriesToTypeRelative();
  // LOG(INFO) << "Registering protos";
  doLog("registering protos");
  registerProtos();
  doLog("registering translations");
  registerAllTranslations();
  doLog("all done initialize");
  // LOG(INFO) << "done initialize";
}

void shutdown(app::GenericApplication*) {
#if JUCE_DEBUG && JUCE_MAC
  Trans::dumpAll();
#endif
  data::deleteDataCenter();
}

}  // namespace slow
}  // namespace rec
