#include "rec/gui/audio/ModeSelector.h"

#include "rec/data/Value.h"
#include "rec/gui/icon/Crosshairs.svg.h"
#include "rec/gui/icon/DraggingHand.svg.h"
#include "rec/gui/icon/Pencil.svg.h"
#include "rec/gui/icon/PointingHand.svg.h"
#include "rec/gui/icon/ZoomIn.svg.h"

using namespace juce;

static const bool ENABLE_SHIFTS = false;
static const int BUTTON_SIZE = 16;
static const int PADDING = 4;

namespace rec {
namespace gui {
namespace audio {

namespace {

template <typename T>
void setImage(ModeSelector* selector, DrawableButton* b, Mode::Action action) {
  b->setImages(ptr<Drawable>(T::create()).get());
  b->addListener(selector);
  selector->addToLayout(b);
  (*selector->buttonMap())[action] = b;
}


enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

}  // namespace

ModeSelector::ModeSelector()
    : Layout("ModeSelector", HORIZONTAL),
      drag_("Drag", DrawableButton::ImageFitted),
      setTime_("setTime", DrawableButton::ImageFitted),
      toggleSelection_("toggleSelection", DrawableButton::ImageFitted),
      zoomIn_("zoomIn", DrawableButton::ImageFitted) {
  using namespace rec::gui::icon;

  setImage<DraggingHand>(this, &drag_, Mode::DRAG);
  // setImage<Pencil>(this, &drawLoopPoints_, Mode::DRAW_LOOP_POINTS);
  setImage<Crosshairs>(this, &setTime_, Mode::SET_TIME);
  setImage<PointingHand>(this, &toggleSelection_, Mode::TOGGLE_SELECTION);
  setImage<ZoomIn>(this, &zoomIn_, Mode::ZOOM_IN);

  setBounds(0, 0, 4 * BUTTON_SIZE + 5 * PADDING, BUTTON_SIZE + 2 * PADDING);
}

DrawableButton* ModeSelector::getButton(const Mode::Action& action) {
  ButtonMap::iterator i = buttons_.find(action);
  return (i == buttons_.end()) ? NULL : i->second;
}

void ModeSelector::onDataChange(const Mode& mode) {
  const Mode::Action action = mode.click();
  MessageManagerLock l;
  for (ButtonMap::iterator i = buttons_.begin(); i != buttons_.end(); ++i)
    i->second->setToggleState(i->first == action, false);
}

void ModeSelector::buttonClicked(Button* button) {
  for (ButtonMap::iterator i = buttons_.begin(); i != buttons_.end(); ++i) {
    if (i->second == button) {
      Mode mode;
      mode.set_click(i->first);
      data()->setValue(mode);
      return;
    }
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

