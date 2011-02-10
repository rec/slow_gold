#ifndef __REC_GUI_CUTANDPASTE__
#define __REC_GUI_CUTANDPASTE__

#include "rec/base/base.h"

namespace rec {
namespace gui {

bool cutToClipboard();
bool copyToClipboard();
bool pasteFromClipboard();
bool canCutOrCopy();
bool canPaste();
bool deleteKeepingClipboard();

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_CUTANDPASTE__
