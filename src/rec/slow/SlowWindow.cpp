#include "rec/slow/SlowWindow.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/source/Stereo.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/base/TranslatedString.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/data/DataCenter.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/gui/WindowPosition.pb.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/AboutWindow.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/RegisterProtos.h"
#include "rec/util/Defaulter.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/NavigatorConfig.pb.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"


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
}

SlowWindow::~SlowWindow() {
  aboutWindow_.reset();
}

void SlowWindow::startListening() {
  app::Window::startListening();
  data::DataListener<music::Metadata>::startListening();
}

void SlowWindow::operator()(const music::Metadata& md) {
  String name = trans("(no file loaded)");
  if (!currentFile()->empty()) {
    File file = data::DataListener<music::Metadata>::getData()->getFile();
    name = str(music::getTitle(md, file.getParentDirectory()));
  }
  thread::callAsync(this, &SlowWindow::setName, name);
}

void SlowWindow::constructInstance() {
  instanceDeleter_.reset(new slow::Instance(this));
  instance_ = instanceDeleter_.get();
  instance_->startListening();
}

void SlowWindow::doStartup() {
  instance_->startup();
}

void SlowWindow::doShutdown() {
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
  TranslatedString::translateAll();
}

void shutdown(app::GenericApplication*) {
#ifdef RECORD_TRANSLATIONS
  dumpTranslations();
#endif
  data::deleteDataCenter();
}

}  // namespace slow
}  // namespace rec
