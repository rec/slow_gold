#ifndef __REC_GUI_PROTO_LEVELMETER__
#define __REC_GUI_PROTO_LEVELMETER__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeLevelMeter(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LEVELMETER__
