#include "rec/gui/proto/Component.h"
#include "rec/gui/proto/Slider.h"
#include "rec/gui/proto/ToggleButton.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeComponent(const ComponentProto& componentProto) {
  unique_ptr<Component> result;
  if (componentProto.has_slider())
    result.reset(makeSlider(componentProto.slider()).release());
  else if (componentProto.has_toggle_button())
    result.reset(makeToggleButton(componentProto.toggle_button()).release());
  else
    LOG(DFATAL) << "Couldn't understand " << componentProto.ShortDebugString();

  return std::move(result);
}

}  // namespace gui
}  // namespace rec
