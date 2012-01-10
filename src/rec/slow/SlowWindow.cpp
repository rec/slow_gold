#include "rec/slow/SlowWindow.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/source/Stereo.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/data/DataCenter.h"
#include "rec/data/MessageRegistrar.h"
#include "rec/data/MessageRegistrarAndMaker.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/gui/WindowPosition.pb.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/AboutWindow.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
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

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", juce::Colours::azure,
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
  File file = data::DataListener<music::Metadata>::getData()->getFile();
  thread::callAsync(this, &SlowWindow::setName, str(music::getTitle(md, file)));
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
    aboutWindowBroadcaster_.broadcast(true);
    MessageManagerLock l;
    aboutWindow_.reset(new AboutWindow(getMainComponent(), instance_,
                                       application()->name(),
                                       application()->version()));
  }
}

void SlowWindow::stopAboutWindow() {
  if (aboutWindow_) {
    MessageManagerLock l;
    aboutWindow_.reset();
    thread::runInNewThread("stopAboutWindow", 4, this, &SlowWindow::turnOffAboutWindow);
  }
}

void SlowWindow::turnOffAboutWindow() {
  Thread::sleep(AboutWindow::FADE_OUT_TIME + 1000);
  aboutWindowBroadcaster_.broadcast(false);
}

void SlowWindow::minimisationStateChanged(bool isNowMinimised) {
  if (!isNowMinimised)
    components()->waveform_->repaint();
}


using namespace rec::data;

void initialize(app::GenericApplication*) {
  MessageRegistrar* r = getDataCenter().registry_.get();

  registerClass<audio::Gain>(r);
  registerClass<audio::source::StereoProto>(r);
  registerClass<audio::stretch::Stretch>(r);
  registerClass<command::CommandMapProto>(r);
  registerClass<command::Commands>(r);
  registerClass<gui::RecentFiles>(r);
  registerClass<gui::WindowPosition>(r);
  registerClass<music::Metadata>(r);
  registerClass<util::LoopPointList>(r);
  registerClass<util::Mode>(r);
  registerClass<util::file::VirtualFile>(r);
  registerClass<util::file::VirtualFileList>(r);
  registerClass<widget::tree::NavigatorConfig>(r);
  registerClass<widget::waveform::WaveformProto>(r);
  registerClass<widget::waveform::ZoomProto>(r);
  registerClass<slow::AppLayout>(r);
  registerClass<slow::GuiSettings>(r);
}

void shutdown(app::GenericApplication*) {
  data::deleteDataCenter();
}

}  // namespace slow
}  // namespace rec
