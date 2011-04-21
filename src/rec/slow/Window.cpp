#include "rec/slow/Window.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Instance.h"

namespace rec {
namespace slow {

Window::Window() : PersistentWindow("SlowGold", juce::Colours::azure,
                                    DocumentWindow::allButtons, true),
                   instance_(new Instance()) {
  computeBounds<AppLayout>();
  setContentComponent(&instance_->components_.mainPage_, true, true);
  setMenuBar(&instance_->menus_);
  setUsingNativeTitleBar(true);
}

Window::~Window() {
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);
  setContentComponent(NULL, false);
}

}  // namespace slow
}  // namespace rec
