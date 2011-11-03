#include "rec/slow/SlowWindow.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/util/Defaulter.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace slow {

SlowWindow::SlowWindow() : app::Window("SlowGold", juce::Colours::azure,
                                       DocumentWindow::allButtons, true) {
}

SlowWindow::~SlowWindow() {}

void SlowWindow::constructInstance() {
  Lock l(lock_);
  instance_.reset(new slow::Instance(this));
}

void SlowWindow::doStartup() {
  Lock l(lock_);
  instance_->startup();
}

Component* SlowWindow::getMainComponent() {
  return instance_->components_->mainPage_->panel();
}

MenuBarModel* SlowWindow::getMenuBarModel() {
  return instance_->menus_.get();
}

void SlowWindow::doComputeBounds() {
  computeBounds<AppLayout>();
}

static Def<LoopPointList> loops(
"loop_point { selected: true }"
);

static Def<AppLayout> layout(
"bounds {\n"
"  top_left { x: 300 y: 100 }\n"
"  dimensions { x: 800 y: 600 }\n"
"}\n"
"directory_y: 175\n"
"waveform_y: 350\n"
"stretchy_y: 175\n"
"clock_x: 250\n"
"songdata_x: 450\n"
"loops_x: 650\n"
);

DefaultRegistry* SlowWindow::getDefaultRegistry() {
  DefaultRegistry* r = new DefaultRegistry;

  r->registerDefault(*loops);
  r->registerDefault(*layout);

  return r;
}

}  // namespace slow
}  // namespace rec

