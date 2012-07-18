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

void readVolumeName(const File& f, VirtualFile* vf) {
  int last = vf->path_size() - 1;
  const string& root = vf->path(last);

#if JUCE_WINDOWS
  String s = f.getFileName();
  if (s.empty())
    LOG(DFATAL) << "Empty " << vf->ShortDebugString() << ", " << str(f);
  else
    vf->set_volume(removeColon(s));

#elif JUCE_MAC
  DCHECK(!f.getFileName().length());
  if (last && root == "Volumes") {
    vf->set_volume_name(vf->path(last - 1));
    vf->mutable_path()->RemoveLast();
    vf->mutable_path()->RemoveLast();
  }
#endif
}

static File getRoot(const VirtualFile& vf) {
  VirtualFile::Type type = vf.type();
  if (type != VirtualFile::VOLUME)
    return getFileTypeDirectory(type);
  const String& volume = str(vf.volume_name());

#if JUCE_WINDOWS
  return File(volume + ":\\");
#elif JUCE_MAC
  return File("/" + (volume.length() ? ("Volumes/" + volume) : String::empty));
#endif
}

}  // namespace

const File getShadowDirectory(const VirtualFile& vf) {
  // DCHECK_NE(vf.type(), VirtualFile::NONE);  // TODO: re-enable this.
  String name = str(VirtualFile::Type_Name(vf.type())).toLowerCase();
  File f = app::getAppFile(name);
  if (vf.volume_name().size())
    f = f.getChildFile(str(vf.volume_name()));

  int len = f.getFullPathName().length();
  for (int i = 0; i < vf.path_size(); ++i)
    len += (vf.path(i).size() + 1);  // Include one for the path separator.

  // Skip path entries until we're short enough.
  int i = 0;
  for (; len > MAX_SHADOW_DIRECTORY_LENGTH && i < vf.path_size(); ++i)
    len -= (vf.path(i).size() + 1);

  for (; i < vf.path_size(); ++i)
    f = f.getChildFile(str(vf.path(i)));

  return f;
}

const VirtualFile toVirtualFile(const File& file, bool useSpecial) {
  VirtualFile::Type type = useSpecial ? getFileType(file) : VirtualFile::VOLUME;
  bool isAbsolutePath = (type == VirtualFile::VOLUME);
  File parent = isAbsolutePath ? File() : getFileTypeDirectory(type);

  VirtualFile vf;
  vf.set_type(type);

  File f = file;
  for (File g = f; f != parent && f != (g = g.getParentDirectory()); f = g)
    vf.add_path(str(f.getFileName()));

  if (isAbsolutePath)
    readVolumeName(f, &vf);

  reverseProto(vf.mutable_path());
  return vf;
}

const File toRealFile(const VirtualFile& vf) {
  File f = getRoot(vf);
  for (int i = 0; i < vf.path_size(); ++i)
    f = f.getChildFile(str(vf.path(i)));

  return f;
}

}  // namespace file
}  // namespace util
}  // namespace rec
