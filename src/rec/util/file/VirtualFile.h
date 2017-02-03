#pragma once

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

// Converts a file on the file system to a virtual file reference, which might
// be relative to one of the special directories.
const VirtualFile toVirtualFile(const File&, bool useSpecial = true);

// The inverse of toVirtualFile.
const File toRealFile(const VirtualFile&);

inline const VirtualFile makeVirtualFile(VirtualFile::Type type) {
    VirtualFile vf;
    vf.set_type(type);
    return vf;
}

// Given a VirtualFile, return the actual directory that shadows it.
const File getShadowDirectory(const VirtualFile&);

inline File getShadowDirectory(VirtualFile::Type type) {
    return getShadowDirectory(makeVirtualFile(type));
}

const uint MAX_WINDOWS_DIRECTORY_SIZE = 260;
const uint MAX_FILENANE_LENGTH = 60;
const uint MAX_SHADOW_DIRECTORY_LENGTH =
    MAX_WINDOWS_DIRECTORY_SIZE - MAX_FILENANE_LENGTH;

}  // namespace file
}  // namespace util
}  // namespace rec
