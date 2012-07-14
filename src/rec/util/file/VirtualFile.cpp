#include <algorithm>

#include "rec/util/file/VirtualFile.h"
#include "rec/app/Files.h"
#include "rec/base/Arraysize.h"
#include "rec/util/ReverseProto.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/Util.h"

using namespace juce;
using namespace google;

namespace rec {
namespace util {
namespace file {

namespace {

typedef google::protobuf::RepeatedPtrField<string> Path;

enum ConversionType {
  TO_SHADOW_FILE, TO_REAL_FILE
};

#if JUCE_WINDOWS
void fixWindowsDriveLetters(String *p, ConversionType conv) {
  if (conv == TO_SHADOW_FILE) {
    if (p->endsWithChar(':'))
      *p = p->dropLastCharacters(1);
  } else {
    if (!p->endsWithChar(':'))
      *p += ':';
  }
}
#endif

const File getRootFile(const String &s) {
#if JUCE_MAC
  if (!s.startsWithChar(File::separator))
    return File(File::separatorString + s);
#endif
  return File(s);
}

const File getFileFromPath(File f, const Path& path, ConversionType conv) {
  for (int i = 0; i < path.size(); ++i) {
    String p = str(path.Get(i));
    bool isNonexistent = (f == File::nonexistent);
    DCHECK(!isNonexistent || (i == 0 && conv == TO_REAL_FILE));
#if JUCE_WINDOWS
    if (i == 0)
      fixWindowsDriveLetters(&p, conv);
#endif
    f = isNonexistent ? getRootFile(p) : f.getChildFile(p);
  }

  return f;
}

#if JUCE_MAC
void fixMacVirtualDirectories(VirtualFile* vf) {
  int last = vf->path_size() - 1;
  const string& root = vf->path(last);

  if (root == "Virtuals" && last != 0) {
    vf->set_volume_name(vf->path(last - 1));
    vf->mutable_path()->RemoveLast();
    vf->mutable_path()->RemoveLast();
  }
}
#endif

}  // namespace

const File getShadowDirectory(const VirtualFile& vf) {
  const File appDir = app::getAppDirectory();
  String name = str(VirtualFile::Type_Name(vf.type())).toLowerCase();
  File f = app::getAppFile(name).getChildFile(str(vf.volume_name()));
  return getFileFromPath(f, vf.path(), TO_SHADOW_FILE);
}

const File toRealFile(const VirtualFile& file) {
  return getFileFromPath(getFileTypeDirectory(file.type()), file.path(),
                         TO_REAL_FILE);
}

const VirtualFile toCompactVirtualFile(const File& file) {
  VirtualFile vf;
  File parent;
  VirtualFile::Type type = getFileType(file);
  if (type) {
    vf.set_type(type);
    parent = getFileTypeDirectory(type);
    DCHECK(parent != File::nonexistent);
  } else {
    vf.set_type(VirtualFile::VOLUME);
  }

  File f = file, p = f;
  for (; f != parent && f != (p = p.getParentDirectory()); f = p)
    vf.add_path(str(f.getFileName()));

#if JUCE_WINDOWS
  if (!type) {
    string lastName = str(f.getFileName());
    if (lastName.size()) {
      fixWindowsDriveLetters(&lastName, TO_SHADOW_FILE);
      vf.add_path(lastName);
    }
  }
#elif JUCE_MAC
  fixMacVirtualDirectories(&vf);
#endif

  reverseProto(vf.mutable_path());
  return vf;
}

const VirtualFile toOriginalVirtualFile(const File& file) {
  VirtualFile vf;
  vf.set_type(VirtualFile::VOLUME);

  File f = file, p = file.getParentDirectory();
  for (; f != p; f = p, p = f.getParentDirectory())
    vf.add_path(str(f.getFileName()));

  string lastName = str(f.getFileName());
  if (lastName.size())
    vf.add_path(lastName);

#if JUCE_MAC
  fixMacVirtualDirectories(&vf);
#endif

  reverseProto(vf.mutable_path());
  return vf;
}

const VirtualFile toVirtualFile(const File& file) {
  DLOG(INFO) << toCompactVirtualFile(file).ShortDebugString();
  return toOriginalVirtualFile(file);
}

}  // namespace file
}  // namespace util
}  // namespace rec
