#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

const File& getFileTypeDirectory(Type type) {
  TypeMap::const_iterator i = map().find(type);
  return (i == map().end()) ? File::nonexistent : i->second.first;
}

const char* getFileTypeName(Type type) {
  TypeMap::const_iterator i = map().find(type);
  return (i == map().end()) ? "<Unknown>" : i->second.second;
}

Type getFileType(const File& f) {
  for (TypeMap::const_iterator i = map().begin(); i != map().end(); ++i) {
    if (f.isAChildOf(i->second.first))
      return i->first;
  }
  return VirtualFile::VOLUME;
}

}  // namespace file
}  // namespace util
}  // namespace rec
