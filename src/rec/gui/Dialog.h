#ifndef __REC_GUI_DIALOG__
#define __REC_GUI_DIALOG__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {
namespace dialog {

void openVirtualFile(Listener<const VirtualFile&> *listener);

}  // namespace dialog
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DIALOG__
