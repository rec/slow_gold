#include "rec/util/file/FileType.h"

namespace rec {
namespace util {
namespace file {

namespace {

typedef std::pair<File, const char*> SpecialLocation;
typedef std::map<VirtualFile::Type, SpecialLocation> TypeMap;

void add(TypeMap* map, VirtualFile::Type type, File::SpecialLocationType loc,
         const char* name) {
  (*map)[type] = std::make_pair(File::getSpecialLocation(loc), name);
}


TypeMap makeTypeMap() {
  TypeMap map;

  add(&map, VirtualFile::MUSIC, File::userMusicDirectory, "<Music>");
  add(&map, VirtualFile::USER, File::userHomeDirectory, "<Home>");
  add(&map, VirtualFile::DESKTOP, File::userDesktopDirectory, "<Desktop>");
  add(&map, VirtualFile::DOCUMENTS, File::userDocumentsDirectory, "<Documents>");
  add(&map, VirtualFile::MOVIES, File::userMoviesDirectory, "<Movies>");

  return map;
};

const TypeMap& typeMap() {
  static const TypeMap map = makeTypeMap();
  return map;
}

}  // namespace

const File& getFileTypeDirectory(VirtualFile::Type type) {
  TypeMap::const_iterator i = typeMap().find(type);
  return (i == typeMap().end()) ? File::nonexistent : i->second.first;
}

const char* getFileTypeName(VirtualFile::Type type) {
  TypeMap::const_iterator i = typeMap().find(type);
  return (i == typeMap().end()) ? "<Unknown>" : i->second.second;
}

VirtualFile::Type getFileType(const File& f) {
  const TypeMap& tm = typeMap();
  for (TypeMap::const_iterator i = tm.end(); i-- != tm.begin(); ) {
    if (f.isAChildOf(i->second.first))
      return i->first;
  }
  return VirtualFile::NONE;
}

}  // namespace file
}  // namespace util
}  // namespace rec
