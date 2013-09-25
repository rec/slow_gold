#ifndef __REC_GUI_PROTO_TIMEDIAL__
#define __REC_GUI_PROTO_TIMEDIAL__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeTimeDial(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_TIMEDIAL__
