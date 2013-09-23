#ifndef __REC_GUI_PROTO_LAYOUT__
#define __REC_GUI_PROTO_LAYOUT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeLayout(const string& name);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LAYOUT__
