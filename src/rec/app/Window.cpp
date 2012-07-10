#include "rec/app/Window.h"

namespace rec {
namespace app {

// Skin.
static const int SLEEP_BEFORE_STARTUP = 0;
static const int SLEEP_AFTER_STARTUP = 10;

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
  constructInstance();

#if JUCE_MAC
  juce::MenuBarModel::setMacMainMenu(getMenuBarModel(), &menu_);
  setMenuBar(NULL);
#else
  setMenuBar(getMenuBarModel());
#endif

  setUsingNativeTitleBar(true);
  setContentOwned(getMainComponent(), false);
}

Window::~Window() {}

void Window::startup() {
  if (SLEEP_BEFORE_STARTUP)
    Thread::sleep(SLEEP_BEFORE_STARTUP);
  // We used to need this so that our GUI has settled down...
  doStartup();

  if (SLEEP_AFTER_STARTUP)
    Thread::sleep(SLEEP_AFTER_STARTUP);
  doPostStartup();
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

