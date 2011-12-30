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
  ModifierKeys keys = ModifierKeys::getCurrentModifiersRealtime();
  if (keys.isCommandDown()) {
    LOG(ERROR) << "Trashing your preferences files.";
    trashPreferences();
  }
  constructInstance();

#if JUCE_MAC
  juce::MenuBarModel::setMacMainMenu(getMenuBarModel(), getAppleMenu());
  setMenuBar(NULL);
#else
  setMenuBar(getMenuBarModel());
#endif

  setUsingNativeTitleBar(true);

  Component* mp = getMainComponent();

  setContentOwned(mp, false);
  setVisible(true);
}

Window::~Window() {}

void Window::startup() {
  Thread::sleep(500);  // We need this so that our GUI has settled down...
  doStartup();
  GuiWriteable::setWriteableAll(true);
}

void Window::shutdown() {
  GuiWriteable::setWriteableAll(false);
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
    // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
  setMenuBar(NULL);
  doShutdown();
}


}  // namespace app
}  // namespace rec

