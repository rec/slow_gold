#ifndef __REC_GUI_PROTO_SLIDER__
#define __REC_GUI_PROTO_SLIDER__

#include "rec/gui/DataSlider.h"
#include "rec/gui/proto/Slider.pb.h"

namespace rec {
namespace gui {

unique_ptr<DataSlider> makeSlider(const SliderProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_SLIDER__
