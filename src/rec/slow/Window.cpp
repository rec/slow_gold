#include "rec/slow/Window.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Instance.h"

namespace rec {
namespace slow {

#define OLD_JUCE 1

Window::Window() : PersistentWindow("SlowGold", juce::Colours::azure,
                                    DocumentWindow::allButtons, true),
                   instance_(new Instance()) {
  Component* mp = &instance_->components_.mainPage_;
  mp->setBounds(0, 0, 1, 1);
#if OLD_JUCE
  setContentComponent(mp, true, true);
#else
  setContentOwned(mp, true);
#endif
  computeBounds<AppLayout>();
  setMenuBar(&instance_->menus_);
  setUsingNativeTitleBar(true);
  setVisible(true);

#if JUCE_MAC
  // TODO: make sure this is in the right place.
  juce::MenuBarModel::setMacMainMenu(&instance_->menus_);
  setMenuBar(NULL);
#endif
}

Window::~Window() {
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);
#if OLD_JUCE
  setContentComponent(NULL, false, true);
#else
  setContentOwned(NULL, false);
#endif
}

}  // namespace slow
}  // namespace rec
