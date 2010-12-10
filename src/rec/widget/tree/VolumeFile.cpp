#include <glog/logging.h>

#include "rec/widget/tree/VolumeFile.h"
#include "rec/data/persist/AppDirectory.h"
#include "rec/util/cd/CDReader.h"

using namespace juce;

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

const File getShadowDirectory(const Volume& v) {
  String name = String(Volume::Type_Name(v.type()).c_str()).toLowerCase();
  File f = data::persist::appDirectory().getChildFile(name);
  return getFile(f, v.name());
}

const File getFile(const VolumeFile& file) {
  return getFile(getVolume(file.volume()), file.path());
}

const File getShadowDirectory(const VolumeFile& file) {
  return getFile(getShadowDirectory(file.volume()), file.path());
}

bool compareVolumes(const Volume& x, const Volume& y) {
  return x.type() < y.type() || (x.type() == y.type() && x.name() < y.name());
}

bool operator==(const Volume& x, const Volume& y) {
  return !(compareVolumes(x, y) || compareVolumes(y, x));
}

bool operator==(const VolumeFile& x, const VolumeFile& y) {
  if (!(x.volume() == y.volume() && x.path_size() == y.path_size()))
    return false;

  for (int i = 0; i < x.path_size(); ++i) {
    if (x.path(i) != y.path(i))
      return false;
  }
  return true;
}

AudioFormatReader* createReader(const VolumeFile& file) {
  const Volume& v = file.volume();
  if (v.type() != Volume::CD)
    return AudioFormatManager::getInstance()->createReaderFor(getFile(file));

  if (!file.path_size()) {
    LOG(ERROR) << "Can't create track for root CD volume for "
               << file.DebugString();
    return NULL;
  }

  int track = String(file.path(0).c_str()).getIntValue();
  return util::cd::createCDTrackReader(v.name().c_str(), track);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
