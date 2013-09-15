#ifndef __REC_GUI_PROTO_LAYOUT__
#define __REC_GUI_PROTO_LAYOUT__

#include "rec/gui/layout/Layout.h"
#include "rec/gui/proto/Layout.pb.h"

namespace rec {
namespace gui {

unique_ptr<Layout> makeLayout(const LayoutProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LAYOUT__
