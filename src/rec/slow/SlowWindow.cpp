#include "rec/slow/SlowWindow.h"

#include "rec/app/GenericApplication.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
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

void SlowWindow::init() {
  app::Window::init();
  data::DataListener<music::Metadata>::init();
}

void SlowWindow::operator()(const music::Metadata& md) {
  String name = Trans("(no file loaded)");
  if (!currentFile()->empty()) {
    File file = data::DataListener<music::Metadata>::getData()->getFile();
    name = str(music::getTitle(md, file.getParentDirectory()));
  }
  thread::callAsync(this, &SlowWindow::setName, name);
}

void SlowWindow::constructInstance() {
  instanceDeleter_.reset(new slow::Instance(this));
  instance_ = instanceDeleter_.get();
  instance_->init();
}

void SlowWindow::doStartup() {
  instance_->startup();
}

void SlowWindow::doShutdown() {
  instance_->stopFilling();

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
#ifdef DEBUG
  Trans::dumpAll();
#endif
  data::deleteDataCenter();
}

}  // namespace slow
}  // namespace rec
