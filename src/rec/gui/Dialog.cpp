#include "rec/gui/Dialog.h"
#include "rec/util/file/Util.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace gui {

namespace {

CriticalSection lock;
bool openDialogOpen = false;

}  // namespace


bool tryToTakeDialogFlag() {
  ScopedLock l(lock);
  if (openDialogOpen)
    return false;

  openDialogOpen = true;
  return true;
}

void replaceDialogFlag() {
  ScopedLock l(lock);
  DCHECK(openDialogOpen);
  openDialogOpen = false;
}

namespace dialog {

bool openVirtualFile(Listener<const VirtualFileList&>* listener,
                     const String& title,
                     const String& patterns,
                     FileChooserFunction function,
                     const File& initial) {
  if (!tryToTakeDialogFlag())
    return false;

  juce::FileChooser chooser(title, initial, patterns, true);
  bool result = (*function)(&chooser);

  if (result)
    (*listener)(file::toVirtualFileList(chooser.getResults()));

  replaceDialogFlag();
  return result;
}

bool openOneFile(Listener<const VirtualFileList&>* listener) {
  return openVirtualFile(listener, "Please choose an audio file",
                         file::audioFilePatterns());
}

}  // namespace dialog
}  // namespace gui
}  // namespace rec
