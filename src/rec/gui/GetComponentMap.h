#ifndef __REC_GUI_GETCOMPONENTMAP__
#define __REC_GUI_GETCOMPONENTMAP__

#include <map>

#include "rec/base/base.h"

namespace rec {
namespace gui {

typedef std::pair<string, Component*> ComponentKey;

typedef std::map<ComponentKey, Component*> ComponentMap;
ComponentMap getComponentMap(Component*);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GETCOMPONENTMAP__
