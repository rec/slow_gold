#include "rec/gui/proto/Component.h"
#include "rec/gui/proto/Slider.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeComponent(const ComponentProto& componentProto) {
  unique_ptr<Component> result;
  if (componentProto.has_slider())
    result.reset(makeSlider(componentProto.slider()).release());
  else
    LOG(DFATAL) << "Couldn't understand " << componentProto.ShortDebugString();

  return std::move(result);
}

}  // namespace gui
}  // namespace rec
