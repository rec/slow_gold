#ifndef __REC_GUI_PROTO_COMBOBOX__
#define __REC_GUI_PROTO_COMBOBOX__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeComboBox(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_COMBOBOX__
