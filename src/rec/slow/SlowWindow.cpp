#include "rec/slow/SlowWindow.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

using namespace juce;

namespace rec {
namespace app {

SlowWindow::SlowWindow()
    : DocumentWindow("SlowGold", Colours::azure, DocumentWindow::allButtons,
                     true) {
  AppLayout layout(persist::data<AppLayout>());
  juce::Rectangle<int> bounds(300, 100, 800, 600);
  if (data->fileReadSuccess())
    bounds = gui::copy(layout.bounds());
  else
    data->set("bounds", Value(gui::copy(bounds)));

  bounds.setWidth(juce::jmax(bounds.getWidth(), 500));
  bounds.setHeight(juce::jmax(bounds.getHeight(), 500));
  bounds.setX(juce::jmax(bounds.getX(), 10));
  bounds.setY(juce::jmax(bounds.getY(), 10));
  setBounds(bounds);
  setResizable(true, false); // resizability is a property of ResizableWindow
  setResizeLimits(1, 1, 8192, 8192);
}

SlowWindow::~SlowWindow() {
  // This next comment might now be vacuous.
  // setting our content component to 0 will delete the current one, and
  // that will in turn delete all its child components. You don't always
  // have to do this explicitly, because the base class's destructor will
  // also delete the content component, but in this case we need to
  // make sure our content comp has gone away before deleting our command
  // manager.
  setContentComponent(NULL, false);
}

void SlowWindow::resized() {
  writeData();
  DocumentWindow::resized();
}

void SlowWindow::writeData() {
  persist::data<AppLayout>()->set("bounds", gui::copy(getBounds()));
}

void SlowWindow::moved() {
  writeData();
  DocumentWindow::moved();
}

void SlowWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace app
}  // namespace rec
