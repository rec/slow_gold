#ifndef __REC_GUI_PROTO_SLIDER__
#define __REC_GUI_PROTO_SLIDER__

#include "rec/gui/DataSlider.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Slider.pb.h"

namespace rec {
namespace gui {

unique_ptr<DataSlider> makeSlider(const SliderProto&, const Constants&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_SLIDER__
