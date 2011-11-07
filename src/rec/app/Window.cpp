#include "rec/app/Window.h"

namespace rec {
namespace app {

Window::Window(const String& name,
               const Colour& bg,
               int requiredButtons,
               bool addToDesktop)
    : PersistentWindow(name, bg, requiredButtons, addToDesktop),
      running_(false) {
}

void Window::initialise() {
  if (running_) {
    LOG(ERROR) << "already running!";
    return;
  }

  constructInstance();
  Component* mp = getMainComponent();
  doComputeBounds();

  setContentOwned(mp, false);

  setMenuBar(getMenuBarModel());
  setUsingNativeTitleBar(true);
  setVisible(true);

#if JUCE_MAC
  // TODO: make sure this is in the right place.
  juce::MenuBarModel::setMacMainMenu(getMenuBarModel());
  setMenuBar(NULL);
#endif

  running_ = true;
}

Window::~Window() {
  shutdown();
}

void Window::startup() {
  // Final startup, done later in another thread.
  doStartup();
  setOKToSaveLayout(true);
}

void Window::shutdown() {
  if (!running_)
    return;

  setOKToSaveLayout(false);
  running_ = false;
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);
}


}  // namespace app
}  // namespace rec

