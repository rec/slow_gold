#ifndef __REC_GUI_PROTO_COMPONENT__
#define __REC_GUI_PROTO_COMPONENT__

#include "rec/base/base.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeComponent(const ComponentProto&, const Constants&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_COMPONENT__
