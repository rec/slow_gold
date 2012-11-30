#include "rec/gui/Dialog.h"

#include "rec/data/DataOps.h"
#include "rec/data/Opener.h"
#include "rec/gui/DialogFiles.pb.h"
#include "rec/util/file/Util.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/VirtualFileList.h"

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

File getDirectoryForDialog(const string& dialogName) {
  DialogFiles df = data::getProto<DialogFiles>(data::global());
  for (int i = 0; i < df.dialog_file_size(); ++i) {
    if (df.dialog_file(i).dialog_name() == dialogName)
      return File(str(df.dialog_file(i).file_name()));
  }

  return File::nonexistent;
}

void setDirectoryForDialog(const string& dialogName, const File& directory) {
  string dir = str(directory.getFullPathName());
  data::Opener<DialogFiles> df(data::global(), CANT_UNDO);
  for (int i = 0; i < df->dialog_file_size(); ++i) {
    if (df->dialog_file(i).dialog_name() == dialogName) {
      df->mutable_dialog_file(i)->set_file_name(dir);
      return;
    }
  }

  DialogFile* newdf = df->add_dialog_file();
  newdf->set_file_name(dir);
  newdf->set_dialog_name(dialogName);
}


DialogLocker::DialogLocker() {
  getDisableBroadcaster()->broadcast(DISABLE);
  Lock l(lock);

  locked_ = !openDialogOpen;
  openDialogOpen = true;
  if (!modalKiller)
    modalKiller = new ModalKiller;
}

DialogLocker::~DialogLocker() {
  {
    Lock l(lock);
    if (locked_) {
      openDialogOpen = false;
      modal = NULL;
    }
  }
  getDisableBroadcaster()->broadcast(ENABLE);
}

Broadcaster<Enable>* DialogLocker::getDisableBroadcaster() {
  static Broadcaster<Enable> disabler;
  return &disabler;
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

template <>
const File toFileList(juce::FileChooser* chooser) {
  return chooser->getResult();
}

template <typename FileList>
bool openVirtualFile(Listener<const FileList&>* listener,
                     const string& dialogName,
                     const String& title,
                     const String& patterns,
                     FileChooserFunction function) {
  DialogLocker l;
  if (!l.isLocked())
    return false;

  File initial = getDirectoryForDialog(dialogName);
  juce::FileChooser chooser(title, initial, patterns, true);
  bool result = (*function)(&chooser);

  if (result) {
    (*listener)(toFileList<FileList>(&chooser));
    setDirectoryForDialog(dialogName, chooser.getResult().getParentDirectory());
  }

  return result;
}

bool openOneAudioFile(Listener<const VirtualFile&>* listener) {
  return openVirtualFile(listener, "audio open", "Please choose an audio file",
                         file::audioFilePatterns());
}

void shutdownDialog() {
  delete modal;
  modal = NULL;
}

template bool openVirtualFile(Listener<const File&>* listener,
                              const string& dialogName,
                              const String& title,
                              const String& patterns,
                              FileChooserFunction function);

}  // namespace dialog
}  // namespace gui
}  // namespace rec
