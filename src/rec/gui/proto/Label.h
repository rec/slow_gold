#ifndef __REC_GUI_PROTO_LABEL__
#define __REC_GUI_PROTO_LABEL__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeLabel(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LABEL__
