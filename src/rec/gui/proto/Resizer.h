#ifndef __REC_GUI_PROTO_RESIZER__
#define __REC_GUI_PROTO_RESIZER__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeResizer(const Context&);
unique_ptr<Component> makeSimpleResizer(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_RESIZER__
