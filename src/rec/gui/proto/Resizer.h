#ifndef __REC_GUI_PROTO_RESIZER__
#define __REC_GUI_PROTO_RESIZER__

#include "rec/gui/SetterResizer.h"
#include "rec/gui/proto/Resizer.pb.h"

namespace rec {
namespace gui {

unique_ptr<SetterResizer> makeResizer(const ResizerProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_RESIZER__
