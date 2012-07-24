#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/MoveFile.h"

namespace rec {
namespace util {
namespace file {

namespace {

const char* const OLD_KEYBOARD_NAME = "KeyPresses";
const char* const NEW_KEYBOARD_NAME = "KeyboardBinding";

typedef VirtualFile::Type Type;

struct Compare {
  bool operator()(Type x, Type y) const { return x > y; }
};

typedef std::pair<File, const char*> SpecialLocation;
typedef std::map<Type, SpecialLocation, Compare> TypeMap;

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

const TypeMap& map() {
  static const TypeMap map = makeTypeMap();
  return map;
}

}  // namespace

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

void moveOldAbsoluteDirectoriesToTypeRelative() {
  for (TypeMap::const_iterator i = map().begin(); i != map().end(); ++i)
    moveTypeDirectory(i->first, i->second.first);
  moveGlobalFiles();
  moveKeyboardFile();
}

}  // namespace file
}  // namespace util
}  // namespace rec