#include "rec/gui/proto/Slider.h"

#include "rec/gui/DataSlider.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeSlider(const Context& context) {
  auto& component = context.component_;
  auto& constants = context.constants_;
  auto& slider = component.slider();

  unique_ptr<DataSlider> dataSlider(
      new DataSlider("",
                     component.tooltip(),
                     slider.caption(),
                     data::splitAddress(component.address()),
                     constants.getDouble(slider.caption_size()),
                     constants.getDouble(slider.text_entry_box_width()),
                     constants.getDouble(slider.text_entry_box_height())));
  if (slider.has_detent())
    dataSlider->setDetent(constants.getDouble(slider.detent()));

  if (slider.has_detent_radius())
    dataSlider->setDetentRadius(constants.getDouble(slider.detent_radius()));

  dataSlider->setRange(constants.getDouble(slider.minimum()),
                       constants.getDouble(slider.maximum()),
                       constants.getDouble(slider.interval()));

  dataSlider->slider()->setTextValueSuffix(slider.suffix_spacing() +
                                           slider.text_suffix());
  return unique_ptr<Component>(dataSlider.release());
}

}  // namespace gui
}  // namespace rec
