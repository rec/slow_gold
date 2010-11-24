#include <glog/logging.h>

#include "rec/widget/tree/VirtualFile.h"
#include "rec/widget/tree/VirtualFile.pb.h"

#include "rec/data/persist/AppDirectory.h"

namespace rec {
namespace widget {
namespace tree {

namespace {

typedef google::protobuf::RepeatedPtrField<string> Path;

const File getFile(File f, const Path& path) {
  for (int i = 0; i < path.size(); ++i)
    f = f.getChildFile(path.Get(i).c_str());

  return f;
}

}  // namespace

const File getVolume(const Volume& v) {
  if (v.type() == Volume::CD) {
    CHECK(v.type() != Volume::CD);
  }

  if (v.type() == Volume::MUSIC) {
    DCHECK_EQ(v.name_size(), 0);
    return File::getSpecialLocation(File::userMusicDirectory);
  }

  if (v.type() == Volume::VOLUME) {
#if JUCE_MAC
    if (v.name_size() == 0)
      return File("/");

    DCHECK_EQ(v.name_size(), 1);
    return File(String("/Volumes/") + v.name(0).c_str());
#else
    return File(v.name());
#endif
  }
  
  CHECK(false) << v.type();
  return File();
}

const File getShadowVolume(const Volume& v) {
  String name = String(Volume::Type_Name(v.type()).c_str()).toLowerCase();
  File f = data::persist::appDirectory().getChildFile(name);
  return getFile(f, v.name());
}

const File getFile(const VolumeFile& file) {
  return getFile(getVolume(file.volume()), file.path());
}

const File getShadowFile(const VolumeFile& file) {
  return getFile(getShadowVolume(file.volume()), file.path());
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
