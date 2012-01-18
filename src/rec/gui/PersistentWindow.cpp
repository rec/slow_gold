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
static const int MIN_Y = 10;
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

  resizeLimits_ = getPeer()->getFrameSize().
    subtractedFrom(getParentMonitorArea());
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT,
                  resizeLimits_.getWidth(), resizeLimits_.getHeight());
}

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::startListening() {
  data::GlobalDataListener<WindowPosition>::startListening();
  (*this)(getProto());
}

void PersistentWindow::operator()(const WindowPosition& p) {
  MessageManagerLock l;
  position_ = p;
  String state = str(p.juce_position());
  thread::callAsync(this, &PersistentWindow::setWindowState, state);
}

void PersistentWindow::setWindowState(const String& state) {
  if (state.length())
    restoreWindowStateFromString(state);

  Rect bounds = getBounds();
  bounds.setWidth(std::min(resizeLimits_.getWidth(),
                           std::max(MIN_WIDTH, bounds.getWidth())));
  bounds.setHeight(std::min(resizeLimits_.getHeight(),
                            std::max(MIN_HEIGHT, bounds.getHeight())));
  bounds.setX(std::max(bounds.getX(), MIN_X));
  bounds.setY(std::max(bounds.getY(), MIN_Y + getTitleBarHeight()));
  setBounds(bounds);
}

void PersistentWindow::moved() {
  MessageManagerLock l;
  DocumentWindow::moved();
  writeData();
}

void PersistentWindow::resized() {
  MessageManagerLock l2;
  DocumentWindow::resized();
  writeData();
}

bool PersistentWindow::isFullScreenSize() const {
  return (getScreenBounds() == getPeer()->getFrameSize().
          subtractedFrom(getParentMonitorArea()));
}

void PersistentWindow::writeData() {
  MessageManagerLock l;
  if (isEnabled()) {
    position_.set_juce_position(str(getWindowStateAsString()));
    requestWrite();
  }
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

void PersistentWindow::doWriteGui() {
  MessageManagerLock l;
  setProto(position_);
}

}  // namespace gui
}  // namespace rec
