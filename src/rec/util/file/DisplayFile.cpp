#include "rec/util/file/DisplayFile.h"
#include "rec/util/file/Util.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

const String getFilename(const VirtualFile& file) {
  return file.path_size() ? str(file.path().end()[-1]) : String(Trans("<none>"));
}

const String getDisplayName(const VirtualFile& file) {
  if (int size = file.path_size())
    return str(file.path(size - 1));

  VirtualFile::Type type = file.type();
  if (type == VirtualFile::VOLUME || type == VirtualFile::CD) {
    string name = file.volume_name();
    eraseVolumePrefix(&name, false);
    return name.empty() ? String(Trans("<Root>")) : str("/" + name);
  } else {
    return getFileTypeName(type);
  }
}

const String getFullDisplayName(const VirtualFile& file) {
  String result = getDisplayName(file) + ":";
  for (int i = 0; i < file.path_size(); ++i)
    result += str(file.path(i) + "/");
  return result;
}

}  // namespace file
}  // namespace util
}  // namespace rec
