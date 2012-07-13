#include "rec/util/file/FileType.h"

namespace rec {
namespace util {
namespace file {

namespace {

typedef std::pair<File::SpecialLocationType, const char*> SpecialLocation;
typedef std::map<VirtualFile::Type, SpecialLocation> TypeMap;

TypeMap makeTypeMap() {
  TypeMap map;

  map[VirtualFile::MUSIC] = std::make_pair(File::userMusicDirectory, "<Music>");
  map[VirtualFile::USER] = std::make_pair(File::userHomeDirectory, "<Home>");
  map[VirtualFile::DESKTOP] = std::make_pair(File::userDesktopDirectory,
                                             "<Desktop>");
  map[VirtualFile::DOCUMENTS] = std::make_pair(File::userDocumentsDirectory,
                                               "<Documents>");
  map[VirtualFile::MOVIES] = std::make_pair(File::userMoviesDirectory, "<Movies>");

  return map;
};

const TypeMap& typeMap() {
  static const TypeMap map = makeTypeMap();
  return map;
}

}  // namespace

const File getFileTypeDirectory(VirtualFile::Type type) {
  TypeMap::const_iterator i = typeMap().find(type);
  return (i == typeMap().end()) ? File() :
    File::getSpecialLocation(i->second.first);
}

const char* getFileTypeName(VirtualFile::Type type) {
  TypeMap::const_iterator i = typeMap().find(type);
  return (i == typeMap().end()) ? "<Unknown>" : i->second.second;
}

}  // namespace file
}  // namespace util
}  // namespace rec
