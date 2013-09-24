#ifndef __REC_GUI_PROTO_TOGGLEBUTTON__
#define __REC_GUI_PROTO_TOGGLEBUTTON__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeToggleButton(const Context&);

}  // namespace gui
}  // namespace rec


#endif  // __REC_GUI_PROTO_TOGGLEBUTTON__
