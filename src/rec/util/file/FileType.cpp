#include "rec/util/file/FileType.h"
#include "rec/util/file/TypeMap.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

const File& getFileTypeDirectory(VirtualFile::Type type) {
    TypeMap::const_iterator i = getTypeMap().find(type);
    return (i == getTypeMap().end()) ? File::nonexistent : i->second.first;
}

const char* getFileTypeName(VirtualFile::Type type) {
    TypeMap::const_iterator i = getTypeMap().find(type);
    return (i == getTypeMap().end()) ? "<Unknown>" : i->second.second;
}

Type getFileType(const File& f) {
    const TypeMap& map = getTypeMap();
    for (TypeMap::const_iterator i = map.begin(); i != map.end(); ++i) {
        if (f.isAChildOf(i->second.first))
            return i->first;
    }
    return VirtualFile::VOLUME;
}

}  // namespace file
}  // namespace util
}  // namespace rec
