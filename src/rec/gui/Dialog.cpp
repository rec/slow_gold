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

bool openVirtualFile(Listener<const VirtualFile&> *listener) {
  ScopedLock l(lock);
  if (openDialogOpen)
    return false;

  openDialogOpen = true;
  juce::FileChooser chooser("Please choose an audio file", File::nonexistent,
                            file::audioFilePatterns(), true);
  bool result = chooser.browseForFileToOpen();

  if (result)
    (*listener)(file::toVirtualFile(chooser.getResult()));

  openDialogOpen = false;
  return result;
}

}  // namespace dialog
}  // namespace gui
}  // namespace rec
