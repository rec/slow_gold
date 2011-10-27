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

static Def<LoopPointList> LOOPS("loop_point { selected: true }");

SlowWindow::SlowWindow() : app::Window("SlowGold", juce::Colours::azure,
                                       DocumentWindow::allButtons, true) {
}

SlowWindow::~SlowWindow() {}

void SlowWindow::constructInstance() {
  Lock l(lock_);
  instance_.reset(new slow::Instance(this));
}

void SlowWindow::startup() {
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



DefaultRegistry* SlowWindow::getDefaultRegistry() {
  DefaultRegistry* r = new data::DefaultRegistry;
  r->registerDefault(*LOOPS);
  return r;
}

}  // namespace slow
}  // namespace rec

