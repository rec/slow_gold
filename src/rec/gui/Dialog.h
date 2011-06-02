#ifndef __REC_GUI_DIALOG__
#define __REC_GUI_DIALOG__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

bool tryToTakeDialogFlag();
void replaceDialogFlag();

namespace dialog {

typedef bool (*FileChooserFunction)(FileChooser*);

inline bool browseForFileToOpen(FileChooser* fc) {
  return fc->browseForFileToOpen();
}

bool openVirtualFile(Listener<const VirtualFileList&>* listener,
                     const String& title,
                     const String& patterns,
                     FileChooserFunction function = &browseForFileToOpen,
                     const File& initial = File::nonexistent);

bool openOneFile(Listener<const VirtualFileList&>* listener);

}  // namespace dialog
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DIALOG__
