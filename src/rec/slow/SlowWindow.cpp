#include "rec/slow/SlowWindow.h"

#include "rec/app/Files.h"
#include "rec/app/GenericApplication.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/AboutWindow.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LegacyDatabase.pb.h"
#include "rec/slow/RegisterProtos.h"
#include "rec/util/file/FixLegacyFiles.h"
#include "rec/util/proto/Defaulter.h"
#include "rec/util/proto/ProtoFile.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/RunOnMessageThread.h"
#include "rec/widget/waveform/Waveform.h"

using namespace juce;

namespace rec {
namespace slow {

namespace {

#define LOG_TO_STDERROR 1

const int FADE_IN_TIME = 1500;
const int FADE_OUT_TIME = 750;

const char WOODSHED_SUFFIX[] = "slow";

void deleteAll(const File& appDir, const String& pattern) {
    DirectoryIterator iterator(appDir, false, pattern);
    while (iterator.next())
        iterator.getFile().deleteFile();
}

// TODO: deleteLogs doesn't work.
void deleteLogs(const File& appDir) {
    deleteAll(appDir, "*.log.*");
    deleteAll(appDir, "il.*");
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

static const auto SHUTDOWN_COUNT = 10;
static const auto SHUTDOWN_WAIT = 50;

class Shutdown : public Thread {
  public:
    Shutdown() : Thread("Shutdown") {}

    void run() override {
        LOG(INFO) << "SlowGold: shutdown starting.";
        sleep(SHUTDOWN_WAIT);
        auto i = 0;
        while (data::getDataCenter()->hasUpdates()) {
            if (++i < SHUTDOWN_COUNT) {
                sleep(SHUTDOWN_WAIT);
            } else {
                LOG(ERROR) << "Data center shut down with updates pending.";
                break;
            }
        }
        LOG(INFO) << "Juce: shutdown starting.";
        getInstance()->shutdown();
        thread::runOnMessageThread(&JUCEApplication::quit);
    }
};

}

SlowWindow::SlowWindow(app::GenericApplication* application)
        : app::Window(application, "SlowGold", Colours::azure,
                                    DocumentWindow::allButtons, true),
            startupFinished_(false) {
    bool check = data::getProto<GuiSettings>().auto_check_for_updates();
    application->setAutoCheckForUpdates(check);
}

SlowWindow::~SlowWindow() {
    Lock l(lock_);
    aboutWindow_.reset();
}


void SlowWindow::init() {
    File appDir = app::getAppDirectory();
    deleteLogs(appDir);
    redirectLogs(appDir);
}

void SlowWindow::constructInstance() {
    instance_.reset(new slow::Instance(this));
    instance_->init();
}

void SlowWindow::doStartup() {
    Lock l(lock_);

    if (instance_->startup()) {
        startupFinished_ = true;
        gotoNextFile();
    } else {
        JUCEApplication::quit();
    }
}

void SlowWindow::gotoNextFile() {
    if (nextFile_ != File::nonexistent) {
        if (nextFile_.hasFileExtension(WOODSHED_SUFFIX)) {
            const MessageMaker& maker = data::getDataCenter()->messageMaker();
            std::unique_ptr<Message> msg(readProtoFile(nextFile_, maker));
            if (!msg)
                LOG(DFATAL) << "Couldn't read woodshed file " << str(nextFile_);
            else if (const LegacyDatabase* db = dynamic_cast<LegacyDatabase*>(msg.get()))
                data::setProto(*db, data::global());
            else
                LOG(DFATAL) << "Database type" << msg->GetTypeName();
        } else {
            getInstance()->currentFile_->setFile(nextFile_);
        }
    }
}

void SlowWindow::doShutdown() {
    instance_->shutdown();
}

void SlowWindow::anotherInstanceStarted(const String& f) {
    Lock l(lock_);

    nextFile_ = File(f.trimCharactersAtEnd("\"").
                                      trimCharactersAtStart("\""));
    if (startupFinished_)
        gotoNextFile();
}

Component* SlowWindow::getMainComponent() {
    return getInstance()->components_->topComponent ();
}

void SlowWindow::activeWindowStatusChanged() {
    program::menuItemsChanged();

    auto& components = getInstance()->components_;
    if (components)
        components->waveform()->repaint();
}

void SlowWindow::startAboutWindow() {
    if (!aboutWindow_) {
        aboutWindow_.reset(new AboutWindow(getMainComponent(),
                                                                              application()->name(),
                                                                              application()->version()));
    }
    Desktop::getInstance().getAnimator().fadeIn(aboutWindow_.get(), FADE_IN_TIME);
}

void SlowWindow::stopAboutWindow() {
    Lock l(lock_);
    if (aboutWindow_) {
        Desktop::getInstance().getAnimator().fadeOut(aboutWindow_.get(),
                                                                                                  FADE_OUT_TIME);
    }
}

void SlowWindow::systemRequestedQuit() {
    getInstance()->currentFile_->saveState();
    shutdownThread_.reset(new Shutdown());
    shutdownThread_->startThread();
}

void SlowWindow::minimisationStateChanged(bool isNowMinimised) {
    if (!isNowMinimised)
        getInstance()->components_->waveform()->repaint();
}

using namespace rec::data;

void initialize(app::GenericApplication*) {
    registerProtos();
    file::fixLegacyFiles();
}

void shutdown(app::GenericApplication*) {
#if JUCE_DEBUG && JUCE_MAC
    Trans::dumpAll();
#endif
    data::deleteDataCenter();
}

}  // namespace slow
}  // namespace rec
