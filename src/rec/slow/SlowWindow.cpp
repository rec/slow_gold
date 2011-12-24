#include "rec/slow/SlowWindow.h"

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
#include "rec/music/Metadata.pb.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/util/Defaulter.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/NavigatorConfig.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

static const Colour BACKGROUND_COLOR = juce::Colours::azure;

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", BACKGROUND_COLOR,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL) {
}

SlowWindow::~SlowWindow() {}

void SlowWindow::constructInstance() {
  instanceDeleter_.reset(new slow::Instance(this));
  instance_ = instanceDeleter_.get();
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
  menus()->menuItemsChanged();
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
