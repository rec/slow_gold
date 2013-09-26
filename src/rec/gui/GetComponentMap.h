#ifndef __REC_GUI_GETCOMPONENTMAP__
#define __REC_GUI_GETCOMPONENTMAP__

#include <unordered_map>

#include "rec/base/base.h"

namespace rec {
namespace gui {

typedef std::unordered_map<string, Component*> ComponentMap;
ComponentMap getComponentMap(Component*);


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GETCOMPONENTMAP__
