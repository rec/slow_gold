
#include "rec/app/RecWindow.h"
#include "rec/app/RecContainer.h"

namespace rec {

RecWindow::RecWindow()
  : DocumentWindow(T("Rec"),
                   Colours::azure,
                   DocumentWindow::allButtons,
                   true) {
  setResizable (true, false); // resizability is a property of ResizableWindow
  setResizeLimits (400, 300, 8192, 8192);

  RecContainer* recContainer = new RecContainer();

  commandManager.registerAllCommandsForTarget(recContainer);
  commandManager.registerAllCommandsForTarget(JUCEApplication::getInstance());

  // this lets the command manager use keypresses that arrive in our window to send
  // out commands
  addKeyListener(commandManager.getKeyMappings());

  // sets the main content component for the window to be this tabbed
  // panel. This will be deleted when the window is deleted.
  setContentComponent(recContainer);

  // this tells the DocumentWindow to automatically create and manage a MenuBarComponent
  // which uses our recContainer as its MenuBarModel
  setMenuBar(recContainer);

  // tells our menu bar model that it should watch this command manager for
  // changes, and send change messages accordingly.
  recContainer->setApplicationCommandManagerToWatch(&commandManager);

  setVisible (true);
  centreWithSize (700, 600);

  setUsingNativeTitleBar(true);
}

RecWindow::~RecWindow() {
#if JUCE_WIN32 || JUCE_LINUX
  deleteAndZero (taskbarIcon);
#endif

  // because we've set the content comp to be used as our menu bar model, we
  // have to switch this off before deleting the content comp..
  setMenuBar(NULL);

#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  MenuBarModel::setMacMainMenu(NULL);
#endif

  // setting our content component to 0 will delete the current one, and
  // that will in turn delete all its child components. You don't always
  // have to do this explicitly, because the base class's destructor will
  // also delete the content component, but in this case we need to
  // make sure our content comp has gone away before deleting our command
  // manager.
  setContentComponent (0, true);
}

void RecWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace rec

