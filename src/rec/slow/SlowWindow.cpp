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

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", BACKGROUND_COLOR,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL) {
}

SlowWindow::~SlowWindow() {}

void SlowWindow::constructInstance() {
  Lock l(gui::PersistentWindow::lock_);
  instanceDeleter_.reset(new slow::Instance(this));
  instance_ = instanceDeleter_.get();
}

void SlowWindow::doStartup() {
  Lock l(gui::PersistentWindow::lock_);
  instance_->startup();
}

void SlowWindow::trashPreferences() {
#if 0
  data::editableFile<gui::WindowPosition>().deleteFile();
  data::editableFile<VirtualFile>().deleteFile();
#endif
}

Component* SlowWindow::getMainComponent() {
  return components()->mainPage_->panel();
}

MenuBarModel* SlowWindow::getMenuBarModel() {
  return menus();
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

static Def<gui::WindowPosition> windowPosition(
"bounds {\n"
"  top_left { x: 300 y: 100 }\n"
"  dimensions { x: 800 y: 600 }\n"
"}\n");

#endif

using namespace rec::data;

void initialize(app::GenericApplication*) {
  MessageRegistrar* r = getDataCenter().registry_.get();

  data::registerClass<audio::Gain>(r);
  data::registerClass<audio::source::StereoProto>(r);
  data::registerClass<audio::stretch::Stretch>(r);
  data::registerClass<command::CommandMapProto>(r);
  data::registerClass<command::Commands>(r);
  data::registerClass<gui::RecentFiles>(r);
  data::registerClass<gui::WindowPosition>(r);
  data::registerClass<music::Metadata>(r);
  data::registerClass<util::LoopPointList>(r);
  data::registerClass<util::Mode>(r);
  data::registerClass<util::file::VirtualFile>(r);
  data::registerClass<util::file::VirtualFileList>(r);
  data::registerClass<widget::tree::NavigatorConfig>(r);
  data::registerClass<widget::waveform::WaveformProto>(r);
  data::registerClass<widget::waveform::ZoomProto>(r);
  data::registerClass<slow::AppLayout>(r);
  data::registerClass<slow::GuiSettings>(r);
}

void SlowWindow::activeWindowStatusChanged() {
  menus()->menuItemsChanged();
}

}  // namespace slow
}  // namespace rec

