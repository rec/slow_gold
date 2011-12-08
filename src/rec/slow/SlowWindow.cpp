#include "rec/slow/SlowWindow.h"
#include "rec/data/DataRegistry.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/WindowPosition.pb.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/util/Defaulter.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace slow {

static const Colour BACKGROUND_COLOR = juce::Colours::azure;

SlowWindow::SlowWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", BACKGROUND_COLOR,
                  DocumentWindow::allButtons, true) {
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

  r->registerMaker<gui::WindowPosition>();
  r->registerMaker<LoopPointList>();

  return r.transfer();
}


}  // namespace slow
}  // namespace rec

