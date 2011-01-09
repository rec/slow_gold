#include "rec/slow/app/RecWindow.h"
#include "rec/slow/app/MainPageComponent.h"
#include "rec/slow/app/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

using namespace juce;

namespace rec {
namespace slow {

RecWindow::RecWindow()
    : DocumentWindow(T("Rec"), Colours::azure, DocumentWindow::allButtons, true),
      container_(new MainPageComponent),
      data_(persist::data<AppLayout>()) {
  if (data_->fileReadSuccess()) {
    juce::Rectangle<int> bounds = gui::copy(data_->get().bounds());
    bounds.setWidth(juce::jmax(bounds.getWidth(), 500));
    bounds.setHeight(juce::jmax(bounds.getHeight(), 500));
    bounds.setX(juce::jmax(bounds.getX(), 50));
    bounds.setY(juce::jmax(bounds.getY(), 50));
    setBounds(bounds);
  } else {
    centreWithSize(700, 600);
    writeData();
  }
  setResizable(true, false); // resizability is a property of ResizableWindow
  setResizeLimits(1, 1, 8192, 8192);

  commandManager_.registerAllCommandsForTarget(&container_);
  commandManager_.registerAllCommandsForTarget(JUCEApplication::getInstance());
  addKeyListener(commandManager_.getKeyMappings());

  setContentComponent(&container_);
  setMenuBar(&container_);

  container_.setApplicationCommandManagerToWatch(&commandManager_);
  setUsingNativeTitleBar(true);
  setVisible (true);
}

RecWindow::~RecWindow() {
#if JUCE_WIN32 || JUCE_LINUX
#if 0
  deleteAndZero (taskbarIcon);
#endif
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
  setContentComponent(NULL, false);
}

void RecWindow::resized() {
  writeData();
  DocumentWindow::resized();
}

void RecWindow::writeData() {
  data_->set("bounds", gui::copy(getBounds()));
}

void RecWindow::moved() {
  writeData();
  DocumentWindow::moved();
}

void RecWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace slow
}  // namespace rec
