#include "rec/gui/Dialog.h"
#include "rec/util/file/Util.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace gui {

namespace {

CriticalSection lock;
bool openDialogOpen = false;
Component* modal = NULL;

class ModalKiller : public juce::DeletedAtShutdown {
 public:
  ModalKiller() {}
  virtual ~ModalKiller() {
    if (modal) {
      modal->exitModalState(0);
      Thread::sleep(1000);
      delete modal;
      modal = NULL;
    }
  }
};

ModalKiller* modalKiller = NULL;

}  // namespace

DialogLocker::DialogLocker() {
  ScopedLock l(lock);
  locked_ = !openDialogOpen;
  openDialogOpen = true;
  if (!modalKiller)
    modalKiller = new ModalKiller;
}

DialogLocker::~DialogLocker() {
  ScopedLock l(lock);
  if (locked_) {
    openDialogOpen = false;
    modal = NULL;
  }
}

void DialogLocker::setModalComponent(Component* c) {
  if (locked_)
    modal = c;
}

namespace dialog {

bool openVirtualFile(Listener<const VirtualFileList&>* listener,
                     const String& title,
                     const String& patterns,
                     FileChooserFunction function,
                     const File& initial) {
  DialogLocker l;
  if (!l.isLocked())
    return false;

  juce::FileChooser chooser(title, initial, patterns, true);
  bool result = (*function)(&chooser);

  if (result)
    (*listener)(file::toVirtualFileList(chooser.getResults()));

  return result;
}

bool openOneFile(Listener<const VirtualFileList&>* listener) {
  return openVirtualFile(listener, "Please choose an audio file",
                         file::audioFilePatterns());
}


void shutdownDialog() {
  delete modal;
  modal = NULL;
}

}  // namespace dialog
}  // namespace gui
}  // namespace rec
