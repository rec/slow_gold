#include "rec/util/file/VolumeFile.h"
#include "rec/util/file/Util.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/cd/CDReader.h"
#include "rec/audio/AudioFormatManager.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {

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
  File f = persist::getApp()->appDir().getChildFile(name);
  return getFile(f, v.name());
}

const File getFile(const VolumeFile& file) {
  return getFile(getVolume(file.volume()), file.path());
}

const File getShadowDirectory(const VolumeFile& file) {
  return getFile(getShadowDirectory(file.volume()), file.path());
}

const String getFilename(const VolumeFile& file) {
  return file.path_size() ? file.path().end()[-1].c_str() : "<none>";
}

const String getDisplayName(const VolumeFile& file) {
  Volume::Type type = file.volume().type();
  if (int size = file.path_size())
    return file.path(size - 1).c_str();

  if (type == Volume::MUSIC)
    return "<Music>";

  if (type == Volume::USER)
    return "<User>";

  if (type == Volume::VOLUME || type == Volume::CD) {
    string name = file.volume().name();
    eraseVolumePrefix(&name, false);
    return name.empty() ? "<Root>" : name.c_str();
  }

  return "<Unknown>";
}

const String getFullDisplayName(const VolumeFile& file) {
  String result = getDisplayName(file) + ":";
  for (int i = 0; i < file.path_size(); ++i)
    result += (file.path(i) + "/").c_str();
  return result;
}

bool compareVolumes(const Volume& x, const Volume& y) {
  return x.type() < y.type() || (x.type() == y.type() && x.name() < y.name());
}

bool compareVolumeFiles(const VolumeFile& x, const VolumeFile& y) {
  if (compareVolumes(x.volume(), y.volume()))
    return true;

  if (compareVolumes(y.volume(), x.volume()))
    return false;

  for (int i = 0; ; i++) {
    bool xDone = (i >= x.path_size() - 1);
    bool yDone = (i >= y.path_size() - 1);
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
    return audio::getAudioFormatManager()->createReaderFor(getFile(file));

  if (!file.path_size()) {
    LOG(ERROR) << "Can't create track for root CD volume for "
               << file.DebugString();
    return NULL;
  }

  int track = String(file.path(0).c_str()).getIntValue();
  return util::cd::createCDTrackReader(v.name().c_str(), track);
}

PositionableAudioSource* createSource(const VolumeFile& file) {
  ptr<AudioFormatReader> reader(createReader(file));
  if (reader)
    return new AudioFormatReaderSource(reader.transfer(), true);
  else
    LOG(ERROR) << "No reader for " << getFullDisplayName(file).toCString();
  return NULL;
}

bool empty(const VolumeFile& f) {
  return !(f.has_volume() && f.volume().has_type() && f.volume().type());
}

VolumeFile toVolumeFile(const File& file) {
  VolumeFile vf;
  vf.mutable_volume()->set_type(Volume::VOLUME);

  File f = file, p = file.getParentDirectory();
  for (; f != p; f = p, p = f.getParentDirectory())
    vf.add_path(f.getFileName().toCString());
  vf.add_path(f.getFileName().toCString());


#if JUCE_MAC
  int last = vf.path_size() - 1;
  const string& root = vf.path(last);

  if (root == "Volumes" && last != 0) {
    vf.mutable_volume()->set_name(vf.path(last - 1));
    vf.mutable_path()->RemoveLast();
    vf.mutable_path()->RemoveLast();
  }

  // TODO: CD things here.
#endif

  for (int i = 0; i < vf.path_size() / 2; ++i)
    vf.mutable_path()->SwapElements(i, vf.path_size() - i - 1);

  return vf;
}

}  // namespace file
}  // namespace util
}  // namespace rec
