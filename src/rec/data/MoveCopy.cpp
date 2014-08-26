#include "rec/data/MoveCopy.h"

namespace rec {
namespace data {

namespace {

struct MoveCopy {
    bool const isCopy_;
    const VirtualFile& file_;
    const string& dialogName_;
    const String& dialogTitle_;

    VirtualFile run() const {
        return VirtualFile();
    }
};

} // namespace


VirtualFile move(const VirtualFile& file,
                 const string& dialogName,
                 const String& dialogTitle) {
    return MoveCopy{false, file, dialogName, dialogTitle}.run();
}

VirtualFile copy(const VirtualFile& file,
                 const string& dialogName,
                 const String& dialogTitle) {

    return MoveCopy{true, file, dialogName, dialogTitle}.run();
}


}  // namespace data
}  // namespace rec
