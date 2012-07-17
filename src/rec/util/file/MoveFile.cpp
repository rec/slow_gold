#include "rec/util/file/MoveFile.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

namespace {

typedef VirtualFile::Type Type;

const char* const OLD_KEYBOARD_NAME = "KeyPresses";
const char* const NEW_KEYBOARD_NAME = "KeyboardBinding";
const bool ENABLE_MOVE = true;

File getShadow(Type type) {
  return file::getShadowDirectory(makeVirtualFile(type));
}

void mkdir(const File& f) {
  if (!f.exists()) {
    if (!f.createDirectory())
      LOG(DFATAL) << "Can't create directory " << str(f);
  }
}

void doMove(const File& source, const File& target) {
  if (source.exists()) {
    if (ENABLE_MOVE) {
      if (!source.moveFileTo(target))
        LOG(ERROR) << "Couldn't move file " << str(source) << " to " << str(target);
    }
    DLOG(INFO) << "Move " << str(source) << " to " << str(target);
  }
}

}  // namespace

void moveTypeDirectory(Type type, const File& special) {
  VirtualFile sourcevf = file::toVirtualFile(special, false);
  doMove(file::getShadowDirectory(sourcevf), getShadow(type));
}

void moveGlobalFiles() {
  File target = getShadow(VirtualFile::GLOBAL);
  mkdir(target);

  File appDir = target.getParentDirectory();
  for (DirectoryIterator it(appDir, false, "*", File::findFiles); it.next(); ) {
    File f(it.getFile());
    File targetFile(target.getChildFile(f.getFileName()));
    doMove(f, targetFile);
  }
}

void moveKeyboardFile() {
  File f = getShadow(VirtualFile::VOLUME).getChildFile(OLD_KEYBOARD_NAME);
  doMove(f, getShadow(VirtualFile::GLOBAL).getChildFile(NEW_KEYBOARD_NAME));
}

}  // namespace file
}  // namespace util
}  // namespace rec
