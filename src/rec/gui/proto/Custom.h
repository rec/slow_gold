#ifndef __REC_GUI_PROTO_CUSTOM__
#define __REC_GUI_PROTO_CUSTOM__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;

unique_ptr<Component> makeCustom(const ComponentProto&, const Constants&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_CUSTOM__
