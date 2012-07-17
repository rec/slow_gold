#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

namespace {

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

File getShadow(Type type) {
  return file::getShadowDirectory(makeVirtualFile(type));
}

static const bool ENABLE_MOVE = true;

void moveTypeDirectory(Type type, const File& special) {
  File target = getShadow(type);
  VirtualFile sourcevf = file::toVirtualFile(special, false);
  File source = file::getShadowDirectory(sourcevf);
  if (!source.exists())
    return;

  if (ENABLE_MOVE) {
    if (!source.moveFileTo(target))
      LOG(ERROR) << "Couldn't move file " << str(source) << " to " << str(target);
  }
  DLOG(INFO) << "Move " << str(source) << " to " << str(target);
}

void moveGlobalFiles() {
  File target = getShadow(VirtualFile::GLOBAL);
  if (!target.exists()) {
    if (!target.createDirectory()) {
      LOG(DFATAL) << "Couldn't create global directory";
      return;
    }
  }

  File appDir = target.getParentDirectory();
  for (DirectoryIterator it(appDir, false, "*", File::findFiles); it.next(); ) {
    File f = it.getFile();
    File targetFile(target.getChildFile(f.getFileName()));
    if (ENABLE_MOVE) {
      if (!f.moveFileTo(targetFile))
        LOG(ERROR) << "Couldn't move file " << str(f) << " to " << str(target);
    }
    DLOG(INFO) << "Moving " << str(f) << " to " << str(targetFile);
  }
}

#if JUCE_MAC
void moveVolumeFiles() {
  File volFile = getShadow(VirtualFile::VOLUME);
  File f = volFile.getChildFile("Volumes");
  DLOG(INFO) << str(f);
  if (f.exists()) {
    for (DirectoryIterator it(f, false, "*", File::findFilesAndDirectories); it.next(); ) {
      File f = it.getFile();
      File targetFile(volFile.getChildFile(f.getFileName()));
      if (ENABLE_MOVE) {
        if (!f.moveFileTo(targetFile))
          LOG(ERROR) << "Couldn't move file " << str(f) << " to " << str(targetFile);
      }
      DLOG(INFO) << "Moving " << str(f) << " to " << str(targetFile);
    }
  } else {
    DLOG(INFO) << "Oops";
  }
}

#endif

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
#if JUCE_MAC
  moveVolumeFiles();
#endif
}

}  // namespace file
}  // namespace util
}  // namespace rec
