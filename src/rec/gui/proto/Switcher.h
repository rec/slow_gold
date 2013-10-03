#ifndef __REC_GUI_PROTO_SWITCHER__
#define __REC_GUI_PROTO_SWITCHER__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeSwitcher(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_SWITCHER__
