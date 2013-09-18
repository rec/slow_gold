#include "rec/gui/proto/Slider.h"

#include "rec/gui/DataSlider.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeSlider(const ComponentProto& component,
                                  const Constants& constants) {
  auto& slider = component.slider();
  unique_ptr<DataSlider> dataSlider(
      new DataSlider(slider.caption(),
                     component.tooltip(),
                     component.address(),
                     constants(slider.caption_size()),
                     constants(slider.text_entry_box_width()),
                     constants(slider.text_entry_box_height())));
  if (slider.has_detent())
    dataSlider->setDetent(constants(slider.detent()));

  if (slider.has_detent_radius())
    dataSlider->setDetentRadius(constants(slider.detent_radius()));

  dataSlider->setRange(constants(slider.minimum()),
                       constants(slider.maximum()),
                       constants(slider.interval()));
  return unique_ptr<Component>(dataSlider.release());
}

}  // namespace gui
}  // namespace rec
