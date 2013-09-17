#include "rec/gui/audio/ModeSelector.h"

#include "rec/data/Value.h"
#include "rec/gui/IconButton.h"

using namespace juce;

// Skin

static const bool ENABLE_SHIFTS = false;
static const int BUTTON_SIZE = 34;
static const int PADDING = 4;
static const int BUTTON_COUNT = 4;

namespace rec {
namespace gui {
namespace audio {

namespace {

void setImage(ModeSelector* selector, LanguageButton* b, Mode::Action action) {
  b->addListener(selector);
  selector->addToPanel(b);
  (*selector->buttonMap())[action] = b;
}

enum Sides {
  STEREO = 1, LEFT, RIGHT, LEFT_PLUS_RIGHT
};

}  // namespace

ModeSelector::ModeSelector()
    : Panel("ModeSelector", HORIZONTAL),
      drag_("Drag", "Drag Mode: Use the mouse to drag the waveform back "
            "and forth"),
      setTime_("setTime", "Set Current Time Mode: Clicking in the waveform "
               "sets the current time."),
      zoomIn_("zoomIn", "Zoom Mode: Clicking on the waveform zooms in on "
              "that point."),
      addLoopPointClick_("CreateClick", "Add loop point mode: clicking on the "
                         "waveform creates a loop point.") {
  SET_BUTTON_IMAGES2(&drag_, DragMode);
  SET_BUTTON_IMAGES2(&setTime_, SetTimeMode);
  SET_BUTTON_IMAGES2(&zoomIn_, ZoomMode);
  SET_BUTTON_IMAGES2(&addLoopPointClick_, AddLoopPointMode);

  setImage(this, &drag_, Mode::DRAG);
  setImage(this, &setTime_, Mode::SET_TIME);
  setImage(this, &zoomIn_, Mode::ZOOM_IN);
  setImage(this, &addLoopPointClick_, Mode::DRAW_LOOP_POINTS);

  minSize_ = juce::Point<int>(BUTTON_COUNT * BUTTON_SIZE +
                              (BUTTON_COUNT + 1) * PADDING,
                              BUTTON_SIZE + 2 * PADDING);
  setBounds(0, 0, minSize_.getX(), minSize_.getY());
}

LanguageButton* ModeSelector::getButton(Mode::Action action) {
  ButtonMap::iterator i = buttons_.find(action);
  return (i == buttons_.end()) ? nullptr : i->second;
}

void ModeSelector::operator()(const Mode& mode) {
  {
    Lock l(lock_);
    mode_ = mode;
  }
  setMode(mode.click());
}

void ModeSelector::setMode(Mode::Action action) {
  for (ButtonMap::iterator i = buttons_.begin(); i != buttons_.end(); ++i)
    i->second->setToggleState(i->first == action, juce::dontSendNotification);
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

