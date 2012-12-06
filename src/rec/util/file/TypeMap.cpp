#include "rec/util/file/TypeMap.h"

namespace rec {
namespace util {
namespace file {

namespace {

void add(TypeMap* map, Type t, File::SpecialLocationType loc, const char* nm) {
  (*map)[t] = std::make_pair(File::getSpecialLocation(loc), nm);
}

TypeMap makeTypeMap() {
  TypeMap m;

  add(&m, VirtualFile::MUSIC, File::userMusicDirectory, "<Music>");
  add(&m, VirtualFile::USER, File::userHomeDirectory, "<Home>");
  add(&m, VirtualFile::DESKTOP, File::userDesktopDirectory, "<Desktop>");
  add(&m, VirtualFile::DOCUMENTS, File::userDocumentsDirectory, "<Documents>");
  add(&m, VirtualFile::MOVIES, File::userMoviesDirectory, "<Movies>");

  return m;
};

}  // namespace

const TypeMap& getTypeMap() {
  static const TypeMap map = makeTypeMap();
  return map;
}

}  // namespace file
}  // namespace util
}  // namespace rec
