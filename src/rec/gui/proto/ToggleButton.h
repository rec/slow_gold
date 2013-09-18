#ifndef __REC_GUI_PROTO_TOGGLEBUTTON__
#define __REC_GUI_PROTO_TOGGLEBUTTON__

#include "rec/gui/SetterToggle.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/ToggleButton.pb.h"

namespace rec {
namespace gui {

unique_ptr<SetterToggle> makeToggleButton(const ToggleButtonProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_TOGGLEBUTTON__
