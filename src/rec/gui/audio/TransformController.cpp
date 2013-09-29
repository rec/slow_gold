#include "rec/gui/audio/TransformController.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/source/Stereo.h"
#include "rec/gui/proto/Layout.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::data;

namespace rec {
namespace gui {
namespace audio {

// Skin

using rec::audio::Gain;
using rec::audio::AudioSettings;

namespace {

const int SLIDER_HEIGHT = 30;
const int FINE_OFFSET = 7;
const int LEFT_PANEL_WIDTH = 67;
const int ENABLE_BUTTON_HEIGHT = 30;
const int COMBO_BOX_HEIGHT = 30;

}  // namespace

using rec::audio::stretch::Stretch;

bool USE_NEW_GUI = not not true;

TransformController::TransformController()
    : Panel("TransformController", HORIZONTAL),
      leftPanel_(gui::makeLayout("LeftTransformPanel", this)),
      rightPanel_(gui::makeLayout("RightTransformPanel", this)) {
  addToPanel(leftPanel_.get(), LEFT_PANEL_WIDTH);
  addToPanel(rightPanel_.get(), 150, -1.0, 250);
}

TransformController::~TransformController() {}

}  // namespace audio
}  // namespace gui
}  // namespace rec

