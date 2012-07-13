#include <algorithm>

#include "rec/util/file/VirtualFile.h"
#include "rec/app/Files.h"
#include "rec/base/Arraysize.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/Util.h"

using namespace juce;
using namespace google;

namespace rec {
namespace util {
namespace file {

namespace {

typedef google::protobuf::RepeatedPtrField<string> Path;

inline String fixPathElement(const String& s) {
  return s.replace(":", "-");
}

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

}  // namespace

const File getShadowDirectory(const VirtualFile& vf) {
  const File appDir = app::getAppDirectory();
  if (!vf.path_size())
    return appDir;

  String name = str(VirtualFile::Type_Name(vf.type())).toLowerCase();
  File f = app::getAppFile(name).getChildFile(str(vf.volume_name()));
  return getFileFromPath(f, vf.path(), TO_SHADOW_FILE);
}

const File toRealFile(const VirtualFile& file) {
  return getFileFromPath(getFileTypeDirectory(file.type()), file.path(),
                         TO_REAL_FILE);
}

const VirtualFile toVirtualFile(const File& file) {
  VirtualFile vf;
  vf.set_type(VirtualFile::VOLUME);

  File f = file, p = file.getParentDirectory();
  for (; f != p; f = p, p = f.getParentDirectory())
    vf.add_path(str(f.getFileName()));

  string lastName = str(f.getFileName());
  if (lastName.size())
    vf.add_path(lastName);


#if JUCE_MAC
  int last = vf.path_size() - 1;
  const string& root = vf.path(last);

  if (root == "Virtuals" && last != 0) {
    vf.set_volume_name(vf.path(last - 1));
    vf.mutable_path()->RemoveLast();
    vf.mutable_path()->RemoveLast();
  }

  // TODO: CD things here (what does this mean?)
#endif

  for (int i = 0; i < vf.path_size() / 2; ++i)
    vf.mutable_path()->SwapElements(i, vf.path_size() - i - 1);

  return vf;
}

#if 0
VirtualFile toCompactVirtualFile(const File& file) {
}
#endif

const File getShadowFile(const VirtualFile& pr, const String& child) {
  return getShadowDirectory(pr).getChildFile(child);
}

}  // namespace file
}  // namespace util
}  // namespace rec
