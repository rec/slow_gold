#include "rec/app/Window.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Menus.h"
#include "rec/slow/Slow.h"

namespace rec {
namespace app {

// TODO: fix this bug!
#define OLD_JUCE

Window::Window(const String& name,
               const Colour& bg,
               int requiredButtons,
               bool addToDesktop)
    : PersistentWindow(name, bg, requiredButtons, addToDesktop) {
}

void Window::initialise() {
  if (running_)
    return;

  initialiseInstance();
  Component* mp = getMainComponent();
  mp->setBounds(0, 0, 1, 1);

#ifdef OLD_JUCE
  setContentComponent(mp, true, true);
#else
  setContentOwned(mp, true);
#endif

  computeBounds<AppLayout>();
  setMenuBar(instance_->menus_.get());
  setUsingNativeTitleBar(true);
  setVisible(true);

#if JUCE_MAC
  // TODO: make sure this is in the right place.
  juce::MenuBarModel::setMacMainMenu(instance_->menus_.get());
  setMenuBar(NULL);
#endif

  running_ = true;
}

Window::~Window() {
  shutdown();
}

void Window::shutdown() {
  if (!running_)
    return;

  running_ = false;
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);

#ifdef OLD_JUCE
  setContentComponent(NULL, false, true);
#else
  setContentOwned(NULL, false);
#endif
}


}  // namespace app
}  // namespace rec

