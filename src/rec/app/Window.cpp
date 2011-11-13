#include "rec/app/Window.h"

namespace rec {
namespace app {

Window::Window(GenericApplication* application,
               const String& name,
               const Colour& bg,
               int requiredButtons,
               bool addToDesktop)
    : PersistentWindow(name, bg, requiredButtons, addToDesktop),
      running_(false),
      application_(application) {
}

void Window::initialise() {
  if (running_) {
    LOG(ERROR) << "already running!";
    return;
  }

  ModifierKeys keys = ModifierKeys::getCurrentModifiersRealtime();
  if (keys.isCommandDown()) {
    LOG(ERROR) << "Trashing your preferences files.";
    trashPreferences();
  }
  getPositionFromData();
  constructInstance();

#if JUCE_MAC
  // TODO: make sure this is in the right place.
  juce::MenuBarModel::setMacMainMenu(getMenuBarModel());
  setMenuBar(NULL);
#else
  setMenuBar(getMenuBarModel());
#endif

  setUsingNativeTitleBar(true);

  Component* mp = getMainComponent();

  setContentOwned(mp, false);
  setVisible(true);

  running_ = true;
}

Window::~Window() {
  shutdown();
}

void Window::startup() {
  // Final startup, done later in another thread.
  doStartup();
  setOKToSavePosition(true);
}

void Window::shutdown() {
  if (!running_)
    return;

  setOKToSavePosition(false);
  running_ = false;
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);
}


}  // namespace app
}  // namespace rec

