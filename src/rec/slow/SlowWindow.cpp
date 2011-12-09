#include "rec/slow/SlowWindow.h"

#include "rec/audio/util/Gain.pb.h"
#include "rec/audio/source/Stereo.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/data/DataRegistry.h"
#include "rec/data/proto/Equals.h"
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
#include "rec/widget/tree/NavigatorConfig.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

static const Colour BACKGROUND_COLOR = juce::Colours::azure;
static const int MILLISECONDS_TILL_TOOLTIP = 700;

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", BACKGROUND_COLOR,
                  DocumentWindow::allButtons, true) {
  tooltipWindow_.reset(new juce::TooltipWindow(this, MILLISECONDS_TILL_TOOLTIP));
}

SlowWindow::~SlowWindow() {}

void SlowWindow::constructInstance() {
  Lock l(gui::PersistentWindow::lock_);
  instance_.reset(new slow::Instance(this));
}

void SlowWindow::doStartup() {
  {
    Lock l(gui::PersistentWindow::lock_);
    instance_->startup();
  }
}

void SlowWindow::trashPreferences() {
  data::editableFile<gui::WindowPosition>().deleteFile();
  data::editableFile<VirtualFile>().deleteFile();
}

Component* SlowWindow::getMainComponent() {
  return instance_->components_->mainPage_->panel();
}

MenuBarModel* SlowWindow::getMenuBarModel() {
  return instance_->menus_.get();
}

static Def<LoopPointList> loops(
"loop_point { selected: true }"
);

#if 0
static Def<AppLayout> layout(
"waveform_y: 200\n"
"control_y: 550\n"

"songdata_x: 350\n"
"loops_x: 650\n"

"transform_x: 350\n"
"controls_x: 650\n"
""
);
#endif

static Def<gui::WindowPosition> windowPosition(
"bounds {\n"
"  top_left { x: 300 y: 100 }\n"
"  dimensions { x: 800 y: 600 }\n"
"}\n");


DefaultRegistry* SlowWindow::getDefaultRegistry() {
  ptr<DefaultRegistry> r(new DefaultRegistry);

  // r->registerDefault(*loops);
  // r->registerDefault(*layout);
  r->registerDefault(*windowPosition);

  return r.transfer();
}

using data::DataRegistry;

DataRegistry* SlowWindow::getDataRegistry() {
  ptr<DataRegistry> r(new DataRegistry);

  r->registerMaker<audio::Gain>();
  r->registerMaker<audio::source::StereoProto>();
  r->registerMaker<audio::stretch::Stretch>();
  r->registerMaker<command::CommandMapProto>();
  r->registerMaker<command::Commands>();
  r->registerMaker<gui::RecentFiles>();
  r->registerMaker<gui::WindowPosition>();
  r->registerMaker<music::Metadata>();
  r->registerMaker<util::LoopPointList>();
  r->registerMaker<util::Mode>();
  r->registerMaker<util::file::VirtualFile>();
  r->registerMaker<util::file::VirtualFileList>();
  r->registerMaker<widget::tree::NavigatorConfig>();
  r->registerMaker<widget::waveform::WaveformProto>();
  r->registerMaker<widget::waveform::ZoomProto>();
  r->registerMaker<slow::AppLayout>();
  r->registerMaker<slow::GuiSettings>();

  return r.transfer();
}


}  // namespace slow
}  // namespace rec

