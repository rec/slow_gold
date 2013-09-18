#include "rec/gui/proto/Slider.h"

namespace rec {
namespace gui {

unique_ptr<DataSlider> makeSlider(const SliderProto& slider,
                                  const Constants& constants) {
  unique_ptr<DataSlider> dataSlider(
      new DataSlider(slider.caption(),
                     slider.tooltip(),
                     slider.address(),
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
  return std::move(dataSlider);
}

}  // namespace gui
}  // namespace rec
