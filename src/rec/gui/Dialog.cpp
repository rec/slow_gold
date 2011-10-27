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

template <typename FileList>
const FileList toFileList(juce::FileChooser*);

template <>
const VirtualFileList toFileList(juce::FileChooser* chooser) {
  return file::toVirtualFileList(chooser->getResults());
}

template <>
const VirtualFile toFileList(juce::FileChooser* chooser) {
  return file::toVirtualFile(chooser->getResult());
}

template <typename FileList>
bool openVirtualFile(Listener<const FileList&>* listener,
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
    (*listener)(toFileList<FileList>(&chooser));

  return result;
}

template
bool openVirtualFile(Listener<const VirtualFileList&>*, const String&,
                     const String&, FileChooserFunction, const File&);

template
bool openVirtualFile(Listener<const VirtualFile&>*, const String&,
                     const String&, FileChooserFunction, const File&);


bool openOneFile(Listener<const VirtualFile&>* listener) {
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
