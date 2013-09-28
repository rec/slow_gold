#ifndef __REC_GUI_PROTO_COMPONENT__
#define __REC_GUI_PROTO_COMPONENT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeComponent(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_COMPONENT__
