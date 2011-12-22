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

static const int MIN_WIDTH = 700;
static const int MIN_HEIGHT = 450;
static const int MIN_X = 10;
static const int MIN_Y = 100;

typedef juce::Rectangle<int> Rect;

PersistentWindow::PersistentWindow(const String& name,
                                   const Colour& bg,
                                   int requiredButtons,
                                   bool addToDesktop)
    : DocumentWindow(name, bg, requiredButtons, addToDesktop),
      running_(false),
      okToSavePosition_(false) {
  setBroughtToFrontOnMouseClick(true);
  setResizable(true, false); // resizability is a property of ResizableWindow

  resizeLimits_ = getPeer()->getFrameSize().subtractedFrom(getParentMonitorArea());
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT,
                  resizeLimits_.getWidth(), resizeLimits_.getHeight());
}

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::fixPosition(WindowPosition* pos) {
  gui::Point* dim = pos->mutable_bounds()->mutable_dimensions();
  int w = std::min(resizeLimits_.getWidth(), std::max(MIN_WIDTH, dim->x()));
  int h = std::min(resizeLimits_.getHeight(), std::max(MIN_HEIGHT, dim->y()));
  dim->set_x(w);
  dim->set_y(h);
}

void PersistentWindow::operator()(const WindowPosition& p) {
  WindowPosition position = p;
  fixPosition(&position);

  {
    Lock l(lock_);
    position_ = position;
  }
  MessageManagerLock l;
  doSetBounds();
}

void PersistentWindow::doSetBounds() {
  juce::Rectangle<int> bounds;
  {
    Lock l(lock_);
    bounds = copy(position_.bounds());
  }

  setBoundsConstrained(bounds);
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
  if (okToSavePosition_) {
    WindowPosition position(getProto());
    juce::Rectangle<int> bounds = getBounds();

    *position.mutable_bounds() = copy(bounds);
    fixPosition(&position);

    Lock l(lock_);
    position_ = position;
    requestWrite();
  }
}

void PersistentWindow::moved() {
  DocumentWindow::moved();
  writeData();
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

void PersistentWindow::doWriteGui() {
  Lock l(lock_);
  if (running_)
    setProto(position_);
}

}  // namespace gui
}  // namespace rec
