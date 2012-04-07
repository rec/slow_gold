#include "rec/gui/audio/CommandBar.h"

#include "rec/gui/IconButton.h"
#include "rec/gui/icon/AddLoopPointButton.svg.h"
#include "rec/gui/icon/AddLoopPointButtonPressed.svg.h"
#include "rec/gui/icon/AddLoopPointButtonDisabled.svg.h"
#include "rec/gui/icon/ZoomOutButton.svg.h"
#include "rec/gui/icon/ZoomOutButtonPressed.svg.h"
#include "rec/gui/icon/ZoomOutButtonDisabled.svg.h"
#include "rec/gui/icon/ZoomToSelectionButton.svg.h"
#include "rec/gui/icon/ZoomToSelectionButtonPressed.svg.h"
#include "rec/gui/icon/ZoomToSelectionButtonDisabled.svg.h"

namespace rec {
namespace gui {
namespace audio {

namespace {

const int BUTTON_SIZE = 39;
const int PADDING = 3;
const int COMMAND_BAR_PAD = -5;

}  // namespace

CommandBar::CommandBar()
    : Layout("CommandBar", HORIZONTAL),
      addLoopPoint_("CreateNow", DrawableButton::ImageFitted),
      zoomOutFull_(Trans("Zoom out"), DrawableButton::ImageFitted),
      zoomToSelection_(Trans("Zoom To Selection"), DrawableButton::ImageFitted) {
  using namespace rec::gui::icon;

  addLoopPoint_.addListener(this);
  zoomOutFull_.addListener(this);
  zoomToSelection_.addListener(this);

  SET_BUTTON_IMAGES3(&addLoopPoint_, AddLoopPointButton);
  SET_BUTTON_IMAGES3(&zoomOutFull_, ZoomOutButton);
  SET_BUTTON_IMAGES3(&zoomToSelection_, ZoomToSelectionButton);

  addLoopPoint_.setTooltip(Trans("Add Loop Point Button: "
                                     "Add a loop point at the current time."));
  zoomOutFull_.setTooltip(Trans("Zoom Out Full Button: "
                                    "Zoom the waveform all the way out."));
  zoomToSelection_.setTooltip(Trans("Zoom To Selection Button: "
                                        "Zoom in or out so the whole selection "
                                        "fits the waveform."));

  addToLayout(&addLoopPoint_, BUTTON_SIZE);
  addToLayout(&zoomOutFull_, BUTTON_SIZE);
  addToLayout(&zoomToSelection_, BUTTON_SIZE);
  addToLayout(&padding_);

  setBounds(0, BUTTON_SIZE + 4 * PADDING,
            3 * BUTTON_SIZE + 2 * PADDING + COMMAND_BAR_PAD,
            BUTTON_SIZE + 2 * PADDING);

  // setImage<Pencil>(this, &drawLoopPoints_, Mode::DRAW_LOOP_POINTS);
}

void CommandBar::buttonClicked(juce::Button *button) {
  if (button == &addLoopPoint_)
    broadcast(command::Command::ADD_LOOP_POINT);

  else if (button == &zoomOutFull_)
    broadcast(command::Command::ZOOM_OUT_FULL);

  else if (button == &zoomToSelection_)
    broadcast(command::Command::ZOOM_TO_SELECTION);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
