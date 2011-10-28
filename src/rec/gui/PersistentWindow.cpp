#include "rec/gui/PersistentWindow.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/Data.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

using namespace juce;
using slow::AppLayout;

PersistentWindow::PersistentWindow(const String& name,
                                   const Colour& bg,
                                   int requiredButtons,
                                   bool addToDesktop)
    : DocumentWindow(name, bg, requiredButtons, addToDesktop),
      data_(NULL), okToSaveLayout_(false) {
}

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
}

void PersistentWindow::resized() {
  writeData();
  DocumentWindow::resized();
}

bool PersistentWindow::isFullScreenSize() const {
  return (getScreenBounds() == getPeer()->getFrameSize().subtractedFrom(
        getParentMonitorArea()));
}

void PersistentWindow::writeData() {
  if (okToSaveLayout_) {
    AppLayout layout(data::editable<AppLayout>()->get());
    juce::Rectangle<int> bounds = getBounds();

    *layout.mutable_bounds() = gui::copy(getBounds());
    data::set(layout);
  }
}

void PersistentWindow::moved() {
  writeData();
  DocumentWindow::moved();
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace gui {
}  // namespace rec {
