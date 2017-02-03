#include "rec/gui/proto/LevelMeter.h"

#include "rec/gui/Orientation.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

using namespace juce;

namespace rec {
namespace gui {

std::unique_ptr<Component> makeLevelMeter(const Context& context) {
    auto& component = context.component_;
    auto& level = component.level_meter();
    return std::unique_ptr<Component>(new audio::LevelMeter(
            "(name)", "(tooltip)",
            level.orientation() == HORIZONTAL,
            level.type(), level.margin()));
}

}  // namespace gui
}  // namespace rec
