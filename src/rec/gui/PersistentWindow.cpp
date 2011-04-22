#include "rec/gui/PersistentWindow.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

using namespace juce;

namespace rec {
namespace gui {

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::setLimitedBounds(const Rect& b) {
  Rect bounds(b);
  bounds.setWidth(juce::jmax(bounds.getWidth(), 500));
  bounds.setHeight(juce::jmax(bounds.getHeight(), 500));
  bounds.setX(juce::jmax(bounds.getX(), 10));
  bounds.setY(juce::jmax(bounds.getY(), 10));
  setBounds(bounds);
  setResizable(true, false); // resizability is a property of ResizableWindow
  setResizeLimits(1, 1, 8192, 8192);
  boundsSet_ = true;
}

void PersistentWindow::resized() {
  writeData();
  DocumentWindow::resized();
}

void PersistentWindow::writeData() {
  // TODO!
  if (boundsSet_)
    persist::appData<slow::AppLayout>()->set("bounds", gui::copy(getBounds()));
}

void PersistentWindow::moved() {
  writeData();
  DocumentWindow::moved();
  getContentComponent()->setBounds(getBounds());
}

void PersistentWindow::closeButtonPressed() {
  // TODO.
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace gui {
}  // namespace rec {
