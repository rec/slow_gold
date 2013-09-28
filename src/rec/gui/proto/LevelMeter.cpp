#include "rec/gui/proto/LevelMeter.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Component> makeLevelMeter(const Context& context) {
  auto& component = context.component_;
  auto& level = component.level_meter();
  return unique_ptr<Component>(new audio::LevelMeter(
      "", "", level.orientation(), level.type(), level.margin()));
}

}  // namespace gui
}  // namespace rec
