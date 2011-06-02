#ifndef __REC_GUI_DIALOG__
#define __REC_GUI_DIALOG__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

class DialogLocker {
 public:
  DialogLocker();
  ~DialogLocker();
  bool isLocked() const { return locked_; }

 private:
  bool locked_;

  DISALLOW_COPY_AND_ASSIGN(DialogLocker);
};

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
