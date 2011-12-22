#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/icon/FullScreen.svg.h"
#include "rec/gui/icon/FullScreenRev.svg.h"
#include "rec/gui/icon/MediaPlay.svg.h"
#include "rec/gui/icon/MediaRecord.svg.h"

namespace rec {
namespace gui {
namespace audio {

namespace {

// TODO: i18n

const int BUTTON_SIZE = 30;
const int PADDING = 4;

}  // namespace

CommandBar::CommandBar()
    : Layout("CommandBar", HORIZONTAL),
      addLoopPoint_("CreateNow", DrawableButton::ImageFitted),
      zoomOut_("Zoom out", DrawableButton::ImageFitted),
      zoomToSelection_("Zoom To Selection", DrawableButton::ImageFitted) {
  using namespace rec::gui::icon;

  addLoopPoint_.addListener(this);
  zoomOut_.addListener(this);
  zoomToSelection_.addListener(this);

  addLoopPoint_.setImages(
                          ptr<Drawable>(icon::MediaPlay::create()).get(), NULL,
                          ptr<Drawable>(icon::MediaRecord::create()).get());

  zoomOut_.setImages(ptr<Drawable>(icon::FullScreen::create()).get(),
                     NULL,
                     ptr<Drawable>(icon::FullScreenRev::create()).get());

  zoomToSelection_.setImages(ptr<Drawable>(icon::FullScreen::create()).get(),
                             NULL,
                             ptr<Drawable>(icon::FullScreenRev::create()).get());

  addLoopPoint_.setTooltip("Add a loop point at the current time.");
  zoomOut_.setTooltip("Zoom the waveform out one step.");
  zoomToSelection_.setTooltip("Zoom in or out so the whole selection "
                              "fits the waveform");

  addToLayout(&addLoopPoint_, BUTTON_SIZE);
  addToLayout(&zoomOut_, BUTTON_SIZE);
  addToLayout(&zoomToSelection_, BUTTON_SIZE);

  setBounds(0, BUTTON_SIZE + 4 * PADDING,
            4 * BUTTON_SIZE + 5 * PADDING, BUTTON_SIZE + 2 * PADDING);

  // setImage<Pencil>(this, &drawLoopPoints_, Mode::DRAW_LOOP_POINTS);
}

void CommandBar::buttonClicked(juce::Button *button) {
  if (button == &addLoopPoint_)
    broadcast(command::Command::ADD_LOOP_POINT);

  else if (button == &zoomOut_)
    broadcast(command::Command::ZOOM_OUT);

  else if (button == &zoomToSelection_)
    broadcast(command::Command::ZOOM_TO_SELECTION);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
