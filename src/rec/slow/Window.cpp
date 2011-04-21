#include "rec/slow/Window.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Instance.h"

namespace rec {
namespace slow {

Window::Window() : PersistentWindow("SlowGold", juce::Colours::azure,
                                    DocumentWindow::allButtons, true),
                   instance_(new Instance()) {
  Component* mp = &instance_->components_.mainPage_;
  mp->setBounds(0, 0, 1, 1);
  setContentComponent(mp, true, true);
  computeBounds<AppLayout>();
  setMenuBar(&instance_->menus_);
  setUsingNativeTitleBar(true);
  setVisible(true);
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
