#pragma once

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

const File getFileTypeDirectory(VirtualFile::Type);
const char* getFileTypeName(VirtualFile::Type);
VirtualFile::Type getFileType(const File&);

}  // namespace file
}  // namespace util
}  // namespace rec
