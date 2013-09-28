#ifndef __REC_GUI_PROTO_TEXT__
#define __REC_GUI_PROTO_TEXT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeText(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_TEXT__
