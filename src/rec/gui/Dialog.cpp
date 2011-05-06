#include "rec/gui/Dialog.h"
#include "rec/util/file/Util.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace gui {
namespace dialog {

namespace {

CriticalSection lock;
bool openDialogOpen = false;

}  // namespace

bool openVirtualFile(Listener<const VirtualFileList&>* listener,
                     const String& title,
                     const String& patterns,
                     FileChooserFunction function,
                     const File& initial) {
  {
    ScopedLock l(lock);
    if (openDialogOpen)
      return false;
    else
      openDialogOpen = true;
  }

  juce::FileChooser chooser(title, initial, patterns, true);
  bool result = (*function)(&chooser);

  if (result)
    (*listener)(file::toVirtualFileList(chooser.getResults()));

  ScopedLock l(lock);
  openDialogOpen = false;
  return result;
}

bool openOneFile(Listener<const VirtualFileList&>* listener) {
  return openVirtualFile(listener, "Please choose an audio file",
                         file::audioFilePatterns());
}

}  // namespace dialog
}  // namespace gui
}  // namespace rec
