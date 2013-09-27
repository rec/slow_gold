#include "rec/gui/audio/TransportController.h"

#include "rec/gui/IconButton.h"
#include "rec/gui/proto/Layout.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/slow/Instance.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

// Skin

namespace {

const int ICON_SIZE = 40;

}  // namespace

using rec::audio::Gain;

TransportController::TransportController()
    : Panel("TransportController", VERTICAL),
      gainPanel_(gui::makeLayout("GainPanel", this)),
      buttonsPanel_(gui::makeLayout("TransportButtonsPanel", this)),
      levelMeter_("LevelMeter", "Level Meter: RMS intensity for left and "
                  "right tracks.") {
  addToPanel(buttonsPanel_.get(), ICON_SIZE);
  addToPanel(gainPanel_.get(), ICON_SIZE);
  addToPanel(&levelMeter_, 20);
}

TransportController::~TransportController() {}

}  // namespace rec
}  // namespace gui
}  // namespace audio
