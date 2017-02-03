#include "rec/util/file/MoveFile.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

namespace {

typedef VirtualFile::Type Type;

const char* const OLD_KEYBOARD = "KeyPresses";
const char* const NEW_KEYBOARD = "KeyboardBinding";
const bool ENABLE_MOVE = true;

File getShadow(Type type) {
    return getShadowDirectory(makeVirtualFile(type));
}

void mkdir(const File& f) {
    if (!f.exists()) {
        if (!f.createDirectory())
            LOG(DFATAL) << "Can't create directory " << str(f);
    }
}

void moveFile(const File& source, const File& target) {
    if (source.exists()) {
        if (ENABLE_MOVE) {
            if (!source.moveFileTo(target))
                LOG(ERROR) << "Couldn't move file " << str(source) << " to " << str(target);
        }
        LOG(INFO) << "Move " << str(source) << " to " << str(target);
    }
}

}  // namespace

void moveTypeDirectory(Type type, const File& special) {
    VirtualFile sourcevf = file::toVirtualFile(special, false);
    moveFile(file::getShadowDirectory(sourcevf), getShadow(type));
}

void moveGlobalFiles() {
    File target = getShadow(VirtualFile::GLOBAL);
    mkdir(target);

    // Remove log files that shouldn't be in this directory.
    for (DirectoryIterator it(target, false, "*.log.*", File::findFiles); it.next(); ) {
        if (!it.getFile().deleteFile())
            LOG(ERROR) << "Couldn't remove " << str(it.getFile());
    }

    // Move non-log files that should be there.
    File appDir = target.getParentDirectory();
    for (DirectoryIterator it(appDir, false, "*", File::findFiles); it.next(); ) {
        File f(it.getFile());
        String name = f.getFileName();
        if (!name.contains(".log."))
            moveFile(f, target.getChildFile(name));
    }
}

File keyboardFile() {
    return getShadowDirectory(VirtualFile::GLOBAL).getChildFile(NEW_KEYBOARD);
}

void moveKeyboardFile() {
    File f = getShadowDirectory(VirtualFile::VOLUME).getChildFile(OLD_KEYBOARD);
    moveFile(f, keyboardFile());
}

const char* keyboardFileName() {
    return NEW_KEYBOARD;
}

}  // namespace file
}  // namespace util
}  // namespace rec
