#ifndef __REC_GUI_PROTO_COMPONENT__
#define __REC_GUI_PROTO_COMPONENT__

#include "rec/base/base.h"
#include "rec/gui/proto/Component.pb.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeComponent(const ComponentProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_COMPONENT__
