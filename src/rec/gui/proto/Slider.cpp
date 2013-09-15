#include "rec/gui/proto/Slider.h"

namespace rec {
namespace gui {

unique_ptr<DataSlider> makeSlider(const SliderProto& slider) {
  unique_ptr<DataSlider> dataSlider(
      new DataSlider(slider.caption(),
                     slider.tooltip(),
                     slider.data_address().type_name(),
                     slider.data_address().address(),
                     slider.caption_size(),
                     slider.text_entry_box_width(),
                     slider.text_entry_box_height()));
  if (slider.has_detent())
    dataSlider->setDetent(slider.detent());

  if (slider.has_detent_radius())
    dataSlider->setDetentRadius(slider.detent_radius());

  dataSlider->setRange(slider.minimum(), slider.maximum(), slider.interval());
  return std::move(dataSlider);
}

}  // namespace gui
}  // namespace rec
