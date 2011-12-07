#include "rec/gui/PersistentWindow.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/util/thread/CallAsync.h"

// #define LOGGING 1

namespace rec {
namespace gui {

using namespace juce;

static const int MIN_WIDTH = 700;
static const int MIN_HEIGHT = 450;
static const int MIN_X = 10;
static const int MIN_Y = 100;
static const int MIN_UPDATE_GAP = 500;

typedef juce::Rectangle<int> Rect;

#ifdef LOGGING
static string toString(const WindowPosition& pos) {
  return str(toString(pos.bounds()));
}
#endif

PersistentWindow::PersistentWindow(const String& name,
                                   const Colour& bg,
                                   int requiredButtons,
                                   bool addToDesktop)
    : DocumentWindow(name, bg, requiredButtons, addToDesktop),
      running_(false),
      okToSavePosition_(false),
      ignoreNextResize_(false),
      needsWrite_(false) {
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
#ifdef LOGGING
  LOG(INFO) << toString(p);
#endif

  WindowPosition position = p;
  fixPosition(&position);

  {
    Lock l(lock_);
#ifndef DONT_FILTER_DUPLICATES
    if (data::equals(position_, position))
      return;  // Filter duplicate messages.
#endif

    position_ = position;

#ifdef FILTER_RESIZES
    ignoreNextResize_ = true;
#endif
  }

#ifdef ASYNC_UPDATES
  thread::callAsync(this, &PersistentWindow::doSetBounds);
#else
  MessageManagerLock l;
  doSetBounds();
#endif
}

void PersistentWindow::doSetBounds() {
  juce::Rectangle<int> bounds;
  {
    Lock l(lock_);
    bounds = copy(position_.bounds());
  }
#ifndef DONT_SET_BOUNDS_CONSTRAINED
  setBoundsConstrained(bounds);
#else
  setBounds(bounds);
#endif
}

void PersistentWindow::resized() {
#ifdef LOGGING
  LOG(INFO) << "resized!";
#endif
  DocumentWindow::resized();
  writeData();
}

bool PersistentWindow::isFullScreenSize() const {
  return (getScreenBounds() == getPeer()->getFrameSize().
          subtractedFrom(getParentMonitorArea()));
}

static int64 time() { return juce::Time::currentTimeMillis(); }

void PersistentWindow::writeData() {
  if (okToSavePosition_) {
    {
      Lock l(lock_);
      if (ignoreNextResize_) {
#ifdef LOGGING
        LOG(INFO) << "resize ignored! ";
#endif
        ignoreNextResize_ = false;
        return;
      }
    }
    WindowPosition position(data::editable<WindowPosition>()->get());
    juce::Rectangle<int> bounds = getBounds();

#ifdef LOGGING
    LOG(INFO) << toString(position);
#endif

    *position.mutable_bounds() = copy(bounds);
    fixPosition(&position);

#ifdef LOGGING
    LOG(INFO) << toString(position);
#endif

#ifdef PERSISTENCE
    data::set(position);
#else
    Lock l(lock_);
    needsWrite_ = true;
    lastUpdateTime_ = time();
    position_ = position;
#endif
  }
}

void PersistentWindow::moved() {
#ifdef LOGGING
  LOG(INFO) << "moved!";
#endif
  DocumentWindow::moved();
  writeData();
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

void PersistentWindow::writeGui() {
  Lock l(lock_);
  if (running_ && needsWrite_ && (time() - lastUpdateTime_) > MIN_UPDATE_GAP) {
    data::set(position_);
    needsWrite_ = false;
  }
}

}  // namespace gui {
}  // namespace rec {
