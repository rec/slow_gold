#include "rec/slow/RecWindow.h"
#include "rec/slow/MainPageComponent.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

using namespace juce;

namespace rec {
namespace slow {

RecWindow::RecWindow()
    : TargetWindow(T("SlowGold"), Colours::azure, DocumentWindow::allButtons, true),
      container_(new MainPageComponent),
      data_(persist::data<AppLayout>()) {
  AppLayout layout(data_->get());
  juce::Rectangle<int> bounds(300, 100, 800, 600);
  if (data_->fileReadSuccess())
    bounds = gui::copy(layout.bounds());
  else
    data_->set("bounds", Value(gui::copy(bounds)));

  bounds.setWidth(juce::jmax(bounds.getWidth(), 500));
  bounds.setHeight(juce::jmax(bounds.getHeight(), 500));
  bounds.setX(juce::jmax(bounds.getX(), 10));
  bounds.setY(juce::jmax(bounds.getY(), 10));
  setBounds(bounds);
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
