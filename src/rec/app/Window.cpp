#include "rec/app/Window.h"

namespace rec {
namespace app {

Window::Window(GenericApplication* application,
               const String& name,
               const Colour& bg,
               int requiredButtons,
               bool addToDesktop)
    : PersistentWindow(name, bg, requiredButtons, addToDesktop),
      application_(application) {
}

void Window::initialise() {
  Lock l(lock_);
  if (running_) {
    LOG(DFATAL) << "already running!";
    return;
  }

  ModifierKeys keys = ModifierKeys::getCurrentModifiersRealtime();
  if (keys.isCommandDown()) {
    LOG(ERROR) << "Trashing your preferences files.";
    trashPreferences();
  }
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
  Lock l(lock_);

  if (running_) {
    doStartup();
    setOKToSavePosition(true);
  }
}

void Window::shutdown() {
  Lock l(lock_);
  if (!running_)
    return;

  running_ = false;

  setOKToSavePosition(false);
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);
}


}  // namespace app
}  // namespace rec

