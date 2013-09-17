#include "rec/gui/audio/CommandBar.h"

#include "rec/gui/IconButton.h"
#include "rec/slow/commands/Command.pb.h"

namespace rec {
namespace gui {
namespace audio {

namespace {

const int BUTTON_SIZE = 39;
const int PADDING = 3;
const int COMMAND_BAR_PAD = -5;

}  // namespace

CommandBar::CommandBar()
    : Panel("CommandBar", HORIZONTAL),
      addLoopPoint_("CreateNow", "Add Loop Point Button: "
                    "Add a loop point at the current time."),
      zoomOutFull_("ZoomOutFull", "Zoom Out Full Button: "
                   "Zoom the waveform all the way out."),
      zoomToSelection_("ZoomToSelection", "Zoom To Selection Button: "
                       "Zoom in or out so the whole selection "
                       "fits the waveform.") {
  addLoopPoint_.addListener(this);
  zoomOutFull_.addListener(this);
  zoomToSelection_.addListener(this);

  SET_BUTTON_IMAGES3(&addLoopPoint_, AddLoopPointButton);
  SET_BUTTON_IMAGES3(&zoomOutFull_, ZoomOutButton);
  SET_BUTTON_IMAGES3(&zoomToSelection_, ZoomToSelectionButton);

  addToPanel(&addLoopPoint_, BUTTON_SIZE);
  addToPanel(&zoomOutFull_, BUTTON_SIZE);
  addToPanel(&zoomToSelection_, BUTTON_SIZE);
  addToPanel(&padding_);

  setBounds(0, BUTTON_SIZE + 4 * PADDING,
            3 * BUTTON_SIZE + 2 * PADDING + COMMAND_BAR_PAD,
            BUTTON_SIZE + 2 * PADDING);

  // setImage<Pencil>(this, &drawLoopPoints_, Mode::DRAW_LOOP_POINTS);
}

void CommandBar::buttonClicked(juce::Button *button) {
  if (button == &addLoopPoint_)
    broadcast(ADD_LOOP_POINT);

  else if (button == &zoomOutFull_)
    broadcast(ZOOM_OUT_FULL);

  else if (button == &zoomToSelection_)
    broadcast(ZOOM_TO_SELECTION);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
