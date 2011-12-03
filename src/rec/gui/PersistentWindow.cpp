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
      okToSavePosition_(false) {
  setBroughtToFrontOnMouseClick(true);
  setResizable(true, false); // resizability is a property of ResizableWindow

  Rect r = getPeer()->getFrameSize().subtractedFrom(getParentMonitorArea());
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT, r.getWidth(), r.getHeight());
}

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::getPositionFromData() {
  DLOG(INFO) << "getPositionFromData";
  data::TypedEditable<WindowPosition>* e = data::editable<WindowPosition>();
  e->addListener(this);
  (*this)(e->get());
}

void PersistentWindow::operator()(const WindowPosition& position) {
  // DLOG(INFO) << position.ShortDebugString();
  {
    Lock l(lock_);
    if (data::equals(position_, position))
      return;  // Filter duplicate messages.

    position_ = position;
  }

  if (true)
    thread::callAsync(this, &PersistentWindow::setBoundsConstrained,
                      copy(position.bounds()));
  else {
    MessageManagerLock l;
    setBoundsConstrained(copy(position.bounds()));
  }
}

void PersistentWindow::resized() {
  // DLOG(INFO) << "resized!";
  DocumentWindow::resized();
  writeData();
}

bool PersistentWindow::isFullScreenSize() const {
  return (getScreenBounds() == getPeer()->getFrameSize().subtractedFrom(
        getParentMonitorArea()));
}

void PersistentWindow::writeData() {
  if (okToSavePosition_) {
    WindowPosition position(data::editable<WindowPosition>()->get());
    juce::Rectangle<int> bounds = getBounds();

    *position.mutable_bounds() = copy(getBounds());
    data::set(position);
  }
}

void PersistentWindow::moved() {
  DLOG(INFO) << "resized!";
  DocumentWindow::moved();
  writeData();
}

void PersistentWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

}  // namespace gui {
}  // namespace rec {
