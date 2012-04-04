#include <algorithm>

#include "rec/util/file/VirtualFile.h"

#include "rec/app/Files.h"
#include "rec/util/file/Util.h"

using namespace juce;
using namespace google;

namespace rec {
namespace util {
namespace file {

namespace {

typedef google::protobuf::RepeatedPtrField<string> Path;

String fixPathElement(const String& s) {
  return s.replace(":", "-");
}

const File getFileFromPath(File f, const Path& path) {
  for (int i = 0; i < path.size(); ++i) {
    String p = str(path.Get(i));
    if (f == File::nonexistent) {
#if JUCE_MAC
      if (!p.startsWithChar(File::separator))
        p = File::separatorString + p;
#endif
      f = File(p);
    } else {
    	f = f.getChildFile(fixPathElement(p));
    }
  }

  return f;
}

const File getRootFile(const VirtualFile& v) {
  if (v.type() == VirtualFile::CD) {
    CHECK(v.type() != VirtualFile::CD);
  }

  if (v.type() == VirtualFile::MUSIC) {
    DCHECK_EQ(v.volume_name(), "");
    return File::getSpecialLocation(File::userMusicDirectory);
  }

  if (v.type() == VirtualFile::VOLUME)
    return v.volume_name().empty() ? File() : File(str(v.volume_name()));

  if (v.type() == VirtualFile::USER) {
    DCHECK_EQ(v.volume_name(), "");
    return File::getSpecialLocation(File::userHomeDirectory);
  }

  DCHECK(false) << v.type();
  return File();
}

}  // namespace

const File getShadowDirectory(const VirtualFile& vf) {
  const File appDir = app::getAppDirectory();
  if (empty(vf))
    return appDir;

  String name = str(VirtualFile::Type_Name(vf.type())).toLowerCase();
  File f = app::getAppFile(name).getChildFile(str(vf.volume_name()));
  return getFileFromPath(f, vf.path());
}

const File getRealFile(const VirtualFile& file) {
  return getFileFromPath(getRootFile(file), file.path());
}

const String getFilename(const VirtualFile& file) {
  return file.path_size() ? str(file.path().end()[-1]) : String(translate("<none>"));
}

const String getDisplayName(const VirtualFile& file) {
  VirtualFile::Type type = file.type();
  if (int size = file.path_size())
    return str(file.path(size - 1));

  if (type == VirtualFile::MUSIC)
    return translate("<Music>");

  if (type == VirtualFile::USER)
    return translate("<User>");

  if (type == VirtualFile::VOLUME || type == VirtualFile::CD) {
    string name = file.volume_name();
    eraseVolumePrefix(&name, false);
    return name.empty() ? translate("<Root>") : str(name);
  }

  return "<Unknown Virtual>";
}

const String getFullDisplayName(const VirtualFile& file) {
  String result = getDisplayName(file) + ":";
  for (int i = 0; i < file.path_size(); ++i)
    result += str(file.path(i) + "/");
  return result;
}

bool compare(const VirtualFile& x, const VirtualFile& y) {
  if (x.type() < y.type())
    return true;

  if (x.type() > y.type())
    return false;

  if (x.volume_name() < y.volume_name())
    return true;

  if (x.volume_name() > y.volume_name())
    return false;

  for (int i = 0; ; i++) {
    bool xDone = (i >= x.path_size());
    bool yDone = (i >= y.path_size());
    if (xDone)
      return !yDone;

    if (yDone)
      return false;

    if (x.path(i) < y.path(i))
      return true;

    if (y.path(i) < x.path(i))
      return false;
  }
}

bool empty(const VirtualFile& f) {
  return !f.has_type();
}

VirtualFile toVirtualFile(const File& file) {
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

VirtualFile toVirtualFile(const string& s) {
  VirtualFile f;
  f.set_type(VirtualFile::VOLUME);
  f.add_path(s);
  return f;
};

namespace {

template <typename Collection>
VirtualFileList toVirtualFileListHelper(const Collection& infiles) {
  VirtualFileList files;
  for (int i = 0; i < infiles.size(); ++i)
    files.add_file()->CopyFrom(file::toVirtualFile(infiles[i]));
  return files;
}

}  // namespace

VirtualFileList toVirtualFileList(const StringArray& files) {
  return toVirtualFileListHelper(files);
}

VirtualFileList toVirtualFileList(const juce::Array<File>& files) {
  return toVirtualFileListHelper(files);
}

void sort(VirtualFileList* v) {
  std::sort(v->mutable_file()->begin(), v->mutable_file()->end(), compare);
}

}  // namespace file
}  // namespace util
}  // namespace rec
