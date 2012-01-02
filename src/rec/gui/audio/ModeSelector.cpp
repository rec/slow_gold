#include "rec/gui/audio/ModeSelector.h"

#include "rec/data/Value.h"
#include "rec/gui/IconButton.h"
#include "rec/gui/icon/AddLoopPointMode.svg.h"
#include "rec/gui/icon/AddLoopPointModeDisabled.svg.h"
#include "rec/gui/icon/DragMode.svg.h"
#include "rec/gui/icon/DragModeDisabled.svg.h"
#include "rec/gui/icon/SetTimeMode.svg.h"
#include "rec/gui/icon/SetTimeModeDisabled.svg.h"
#include "rec/gui/icon/ZoomMode.svg.h"
#include "rec/gui/icon/ZoomModeDisabled.svg.h"

using namespace juce;

// TODO: i18n

static const bool ENABLE_SHIFTS = false;
static const int BUTTON_SIZE = 24;
static const int PADDING = 4;
static const int BUTTON_COUNT = 4;

namespace rec {
namespace gui {
namespace audio {

namespace {

void setImage(ModeSelector* selector, DrawableButton* b, Mode::Action action,
              const String& tooltip) {
  b->addListener(selector);
  selector->addToLayout(b);
  (*selector->buttonMap())[action] = b;
  b->setTooltip(tooltip);
}

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

}  // namespace

ModeSelector::ModeSelector()
    : Layout("ModeSelector", HORIZONTAL),
      drag_("Drag", DrawableButton::ImageFitted),
      setTime_("setTime", DrawableButton::ImageFitted),
      zoomIn_("zoomIn", DrawableButton::ImageFitted),
      addLoopPointClick_("CreateClick", DrawableButton::ImageFitted) {
  using namespace rec::gui::icon;

  SET_BUTTON_IMAGES2(&drag_, DragMode);
  SET_BUTTON_IMAGES2(&setTime_, SetTimeMode);
  SET_BUTTON_IMAGES2(&zoomIn_, ZoomMode);
  SET_BUTTON_IMAGES2(&addLoopPointClick_, AddLoopPointMode);

  setImage(this, &drag_, Mode::DRAG,
           "Drag mode: use the mouse to drag the waveform back and forth");
  setImage(this, &setTime_, Mode::SET_TIME,
           "Set current time mode: clicking in the waveform sets the current time.");
  setImage(this, &zoomIn_, Mode::ZOOM_IN,
           "Zoom mode: clicking on the waveform zooms in on that point.");

  setImage(this, &addLoopPointClick_, Mode::DRAW_LOOP_POINTS,
           "Add loop point mode: clicking on the waveform creates a loop point.");

  minSize_ = juce::Point<int>(BUTTON_COUNT * BUTTON_SIZE +
                              (BUTTON_COUNT + 1) * PADDING,
                              BUTTON_SIZE + 2 * PADDING);
  setBounds(0, 0, minSize_.getX(), minSize_.getY());
}

DrawableButton* ModeSelector::getButton(const Mode::Action& action) {
  ButtonMap::iterator i = buttons_.find(action);
  return (i == buttons_.end()) ? NULL : i->second;
}

void ModeSelector::operator()(const Mode& mode) {
  {
    Lock l(lock_);
    mode_ = mode;
  }
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
      setProto(mode);
      return;
    }
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

