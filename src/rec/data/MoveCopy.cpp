#include "rec/data/MoveCopy.h"

#if 0

#include "rec/gui/Dialog.h"

namespace rec {
namespace data {

namespace {

struct MoveCopy : Listener<const File&> {
    bool const isCopy_;
    const VirtualFile& file_;
    const string& dialogName_;
    const String& dialogTitle_;
    File newFile_ = ;
    VirtualFile result_ = VirtualFile::default_instance();

    void operator()(const File& f) override {
        newFile_ = f;
    }

    void run() {
        result_.Clear();
        auto realFile = toRealFile(file_);
        auto extension = realFile.getFileExtension();
        if (gui::dialog::saveVirtualFile(
                this, dialogName_, dialogTitle_, "*" + extension)) {
            if (isCopy_)
                copy();
            else
                move();

        }
    }

    void copy() {
    }

    void move() {
    }
};

VirtualFile moveCopy(bool isCopy,
                     const VirtualFile& file,
                     const string& dialogName,
                     const String& dialogTitle) {
    MoveCopy mc{isCopy, file, dialogName, dialogTitle, File::nonexistent
}

} // namespace

VirtualFile move(const VirtualFile& file,
                 const string& dialogName,
                 const String& dialogTitle) {
    return MoveCopy{false, file, dialogName, dialogTitle, File::nonexistent}.run();
}

VirtualFile copy(const VirtualFile& file,
                 const string& dialogName,
                 const String& dialogTitle) {

    return MoveCopy{true, file, dialogName, dialogTitle}.run();
}


}  // namespace data
}  // namespace rec
#endif
