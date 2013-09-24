#ifndef __REC_GUI_PROTO_HELP__
#define __REC_GUI_PROTO_HELP__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeHelp(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_HELP__
