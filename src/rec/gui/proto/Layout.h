#ifndef __REC_GUI_PROTO_LAYOUT__
#define __REC_GUI_PROTO_LAYOUT__

#include "rec/gui/proto/Panel.h"
#include "rec/gui/proto/Layout.pb.h"

namespace rec {
namespace gui {

unique_ptr<Panel> makePanel(const LayoutProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LAYOUT__
