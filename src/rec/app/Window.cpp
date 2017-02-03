#include "rec/app/Window.h"
#include "rec/program/JuceModel.h"

namespace rec {
namespace app {

// Skin.
//static const int SLEEP_BEFORE_STARTUP = 0;
//static const int SLEEP_AFTER_STARTUP = 0;

Window::Window(GenericApplication* application,
               const String& name,
               const Colour& bg,
               int requiredButtons,
               bool addToDesktop)
        : PersistentWindow(name, bg, requiredButtons, addToDesktop),
          application_(application) {
}

void Window::initialise() {
    constructInstance();

#if JUCE_MAC
    juce::MenuBarModel::setMacMainMenu(program::juceModel(), &menu_);
    setMenuBar(nullptr);
#else
    setMenuBar(program::juceModel());
#endif

    setUsingNativeTitleBar(true);
    setContentOwned(getMainComponent(), false);
}

Window::~Window() {}

void Window::startup() {
    doStartup();
    GuiWriteable::setWriteableAll(true);
}

void Window::shutdown() {
    GuiWriteable::setWriteableAll(false);
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
        // Why isn't this in GenericApplication?
    MenuBarModel::setMacMainMenu(nullptr);
#endif
    setMenuBar(nullptr);
    doShutdown();
}

}  // namespace app
}  // namespace rec
