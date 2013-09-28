#ifndef __REC_GUI_PROTO_BUTTON__
#define __REC_GUI_PROTO_BUTTON__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeButton(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_BUTTON__
