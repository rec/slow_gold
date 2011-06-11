#include "rec/gui/PersistentWindow.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

using namespace juce;
using slow::AppLayout;


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
  okToSaveLayout_ = true;
}

void PersistentWindow::resized() {
  writeData();
  DocumentWindow::resized();
}

void PersistentWindow::writeData() {
  if (okToSaveLayout_) {
    AppLayout layout(persist::get<AppLayout>());
    juce::Rectangle<int> bounds = getBounds();
    bool full = isFullScreen() || (getScreenBounds() == getParentMonitorArea());
#if 0
    DLOG(INFO) << str(getScreenBounds().toString())
               << ", "
               << str(getParentMonitorArea().toString());
#endif
    layout.set_full_screen(full);
    if (!full)
      *layout.mutable_bounds() = gui::copy(getBounds());
    persist::set(layout);
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
