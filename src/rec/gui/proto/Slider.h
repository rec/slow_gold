#ifndef __REC_GUI_PROTO_SLIDER__
#define __REC_GUI_PROTO_SLIDER__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeSlider(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_SLIDER__
