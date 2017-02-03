#pragma once

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

void moveTypeDirectory(VirtualFile::Type type, const File& special);
void moveGlobalFiles();
void moveKeyboardFile();
File keyboardFile();
const char* keyboardFileName();

}  // namespace file
}  // namespace util
}  // namespace rec
