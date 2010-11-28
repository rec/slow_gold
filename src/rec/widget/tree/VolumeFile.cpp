#include <glog/logging.h>

#include "rec/widget/tree/VolumeFile.h"
#include "rec/data/persist/AppDirectory.h"

namespace rec {
namespace widget {
namespace tree {

namespace {

const File getFile(const File& f, const string& path) {
  return f.getChildFile(path.c_str());
}

typedef google::protobuf::RepeatedPtrField<string> Path;

const File getFile(File f, const Path& path) {
  for (int i = 0; i < path.size(); ++i)
    f = getFile(f, path.Get(i).c_str());

  return f;
}

}  // namespace

const File getVolume(const Volume& v) {
  if (v.type() == Volume::CD) {
    CHECK(v.type() != Volume::CD);
  }

  if (v.type() == Volume::MUSIC) {
    DCHECK_EQ(v.name(), "");
    return File::getSpecialLocation(File::userMusicDirectory);
  }

  if (v.type() == Volume::VOLUME) {
#if JUCE_MAC
    if (v.name().empty())
      return File("/");
#else
    DCHECK(!v.name().empty());
#endif
    return File(v.name().c_str());
  }

  if (v.type() == Volume::USER) {
    DCHECK_EQ(v.name(), "");
    return File::getSpecialLocation(File::userHomeDirectory);
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

bool compareVolumes(const Volume& x, const Volume& y) {
  return x.type() < y.type() || (x.type() == y.type() && x.name() < y.name());
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
