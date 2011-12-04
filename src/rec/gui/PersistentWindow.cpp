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

static const int MIN_WIDTH = 600;
static const int MIN_HEIGHT = 440;
static const int MIN_X = 10;
static const int MIN_Y = 100;

typedef juce::Rectangle<int> Rect;

PersistentWindow::PersistentWindow(const String& name,
                                   const Colour& bg,
                                   int requiredButtons,
                                   bool addToDesktop)
    : DocumentWindow(name, bg, requiredButtons, addToDesktop),
      okToSavePosition_(false),
      ignoreNextResize_(false) {
  setBroughtToFrontOnMouseClick(true);
  setResizable(true, false); // resizability is a property of ResizableWindow

  resizeLimits_ = getPeer()->getFrameSize().subtractedFrom(getParentMonitorArea());
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT,
                  resizeLimits_.getWidth(), resizeLimits_.getHeight());
}

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::getPositionFromData() {
  data::TypedEditable<WindowPosition>* e = data::editable<WindowPosition>();
  e->addListener(this);
  (*this)(e->get());
}

void PersistentWindow::fixPosition(WindowPosition* pos) {
  gui::Point* dim = pos->mutable_bounds()->mutable_dimensions();
  int w = std::min(resizeLimits_.getWidth(), std::max(MIN_WIDTH, dim->x()));
  int h = std::min(resizeLimits_.getHeight(), std::max(MIN_HEIGHT, dim->y()));
  dim->set_x(w);
  dim->set_y(h);
}

void PersistentWindow::operator()(const WindowPosition& p) {
  // DLOG(INFO) << "data! " << p.ShortDebugString();

  WindowPosition position = p;
  fixPosition(&position);

  {
    Lock l(lock_);
    if (data::equals(position_, position))
      return;  // Filter duplicate messages.

    position_ = position;
#ifdef FILTER_RESIZES
    ignoreNextResize_ = true;
#endif
  }

  juce::Rectangle<int> bounds = copy(position.bounds());
#ifndef ASYNC_UPDATES
  thread::callAsync(this, &PersistentWindow::doSetBounds, bounds);
#else
  MessageManagerLock l;
  doSetBounds(bounds);
#endif
}

void PersistentWindow::doSetBounds(juce::Rectangle<int> bounds) {
#ifdef SET_BOUNDS_CONSTRAINED
  setBoundsConstrained(bounds);
#else
  setBounds(bounds);
#endif
}

void PersistentWindow::resized() {
  // DLOG(INFO) << "resized!";
  DocumentWindow::resized();
  writeData();
}

bool PersistentWindow::isFullScreenSize() const {
  return (getScreenBounds() == getPeer()->getFrameSize().
          subtractedFrom(getParentMonitorArea()));
}

void PersistentWindow::writeData() {
  if (okToSavePosition_) {
    {
      Lock l(lock_);
      if (ignoreNextResize_) {
        DLOG(INFO) << "resize ignored! ";
        ignoreNextResize_ = false;
        return;
      }
    }
    WindowPosition position(data::editable<WindowPosition>()->get());
    juce::Rectangle<int> bounds = getBounds();

    *position.mutable_bounds() = copy(getBounds());
    fixPosition(&position);
    // DLOG(INFO) << "write data! " << position.ShortDebugString();
    data::set(position);
  }
}

void PersistentWindow::moved() {
  // DLOG(INFO) << "moved!";
  DocumentWindow::moved();
  writeData();
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace gui {
}  // namespace rec {
