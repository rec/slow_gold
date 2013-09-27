#ifndef __REC_GUI_PROTO_LAYOUT__
#define __REC_GUI_PROTO_LAYOUT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeLayout(const string& name, Component* parent);
unique_ptr<Component> makeLayoutComp(const Context&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LAYOUT__
