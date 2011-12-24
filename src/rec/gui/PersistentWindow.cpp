#include "rec/gui/PersistentWindow.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

using namespace juce;

static const int MIN_WIDTH = 800;
static const int MIN_HEIGHT = 550;
static const int MIN_X = 10;
static const int MIN_Y = 100;
static const int X_FUDGE = 50;
static const int Y_FUDGE = 50;

typedef juce::Rectangle<int> Rect;

PersistentWindow::PersistentWindow(const String& name,
                                   const Colour& bg,
                                   int requiredButtons,
                                   bool addToDesktop)
    : DocumentWindow(name, bg, requiredButtons, addToDesktop) {
  setBroughtToFrontOnMouseClick(true);
  setResizable(true, false);

  resizeLimits_ = getPeer()->getFrameSize().subtractedFrom(getParentMonitorArea());
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT,
                  resizeLimits_.getWidth(), resizeLimits_.getHeight());
  (*this)(getProto());
}

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::operator()(const WindowPosition& p) {
  {
    Lock l(lock_);
    position_ = p;
  }
  MessageManagerLock l;
  if (!p.juce_position().empty())
    restoreWindowStateFromString(str(p.juce_position()));

  Rect bounds = getBounds();
  bounds.setWidth(std::min(resizeLimits_.getWidth(),
                           std::max(MIN_WIDTH, bounds.getWidth())));
  bounds.setHeight(std::min(resizeLimits_.getHeight(),
                            std::max(MIN_HEIGHT, bounds.getHeight())));
  setBounds(bounds);
}

void PersistentWindow::moved() {
  DocumentWindow::moved();
  writeData();
}

void PersistentWindow::resized() {
  DocumentWindow::resized();
  writeData();
}

bool PersistentWindow::isFullScreenSize() const {
  return (getScreenBounds() == getPeer()->getFrameSize().
          subtractedFrom(getParentMonitorArea()));
}

void PersistentWindow::writeData() {
  if (isEnabled()) {
    Lock l(lock_);
    position_.set_juce_position(str(getWindowStateAsString()));
    requestWrite();
  }
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

void PersistentWindow::doWriteGui() {
  Lock l(lock_);
  setProto(position_);
}

}  // namespace gui
}  // namespace rec
