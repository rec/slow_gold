#pragma once

#include "rec/util/Enable.h"
#include "rec/util/Listener.h"

namespace rec {
namespace gui {

class DialogLocker {
  public:
    DialogLocker();
    ~DialogLocker();
    bool isLocked() const { return locked_; }
    void setModalComponent(Component* c);

    static Broadcaster<Enable>* getDisableBroadcaster();

  private:
    bool locked_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(DialogLocker);
};

File getDirectoryForDialog(const string& dialogName);
void setDirectoryForDialog(const string& dialogName, const File& directory);

namespace dialog {

typedef bool (*FileChooserFunction)(FileChooser*);

inline bool browseForFileToOpen(FileChooser* fc) {
    return fc->browseForFileToOpen();
}

inline bool browseForFileToSave(FileChooser* fc) {
    return fc->browseForFileToSave(true);
}

template <typename FileList>
bool openVirtualFile(Listener<const FileList&>* listener,
                                          const string& dialogName,
                                          const String& title,
                                          const String& patterns,
                                          FileChooserFunction function = &browseForFileToOpen);

inline bool saveVirtualFile(Listener<const File&>* listener,
                                                        const string& dialogName,
                                                        const String& title,
                                                        const String& patterns) {
    return openVirtualFile(listener, dialogName, title, patterns,
                                                  &browseForFileToSave);
}

bool openOneAudioFile(Listener<const VirtualFile&>* listener);

void shutdownDialog();

}  // namespace dialog
}  // namespace gui
}  // namespace rec
