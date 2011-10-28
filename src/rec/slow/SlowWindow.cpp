#include "rec/slow/SlowWindow.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Menus.h"
#include "rec/slow/Slow.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Defaulter.h"

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
  return &instance_->components_->mainPage_;
}

MenuBarModel* SlowWindow::getMenuBarModel() {
  return instance_->menus_.get();
}

void SlowWindow::doComputeBounds() {
  computeBounds<AppLayout>();
}

using data::DefaultRegistry;

static Def<LoopPointList> loops(
"loop_point { selected: true }"
);

static Def<AppLayout> layout(
"bounds { "
"  top_left { x: 300 y: 100 }"
"  dimensions { x: 800 y: 600 }"
"} "
"directory_y: 175 "
"waveform_y: 350 "
"stretchy_y: 175 "
"clock_x: 250 "
"songdata_x: 450 "
"loops_x: 650 "
"}"
);

DefaultRegistry* SlowWindow::getDefaultRegistry() {
  DefaultRegistry* r = new data::DefaultRegistry;

  r->registerDefault(*loops);
  r->registerDefault(*layout);

  return r;
}

}  // namespace slow
}  // namespace rec

