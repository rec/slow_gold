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

const File getVolume(const VolumeFile& v) {
  if (v.type() == VolumeFile::CD) {
    CHECK(v.type() != VolumeFile::CD);
  }

  if (v.type() == VolumeFile::MUSIC) {
    DCHECK_EQ(v.name(), "");
    return File::getSpecialLocation(File::userMusicDirectory);
  }

  if (v.type() == VolumeFile::VOLUME) {
#if JUCE_MAC
    if (v.name().empty())
      return File("/");
#else
    DCHECK(!v.name().empty());
#endif
    return File(v.name().c_str());
  }

  if (v.type() == VolumeFile::USER) {
    DCHECK_EQ(v.name(), "");
    return File::getSpecialLocation(File::userHomeDirectory);
  }

  CHECK(false) << v.type();
  return File();
}

const File getShadowDirectory(const VolumeFile& vf) {
  String name = String(VolumeFile::Type_Name(vf.type()).c_str()).toLowerCase();
  File f = persist::getApp()->appDir().getChildFile(name);
  return getFile(getFile(f, vf.name()), vf.path());
}

const File getFile(const VolumeFile& file) {
  return getFile(getVolume(file), file.path());
}

const String getFilename(const VolumeFile& file) {
  return file.path_size() ? file.path().end()[-1].c_str() : "<none>";
}

const String getDisplayName(const VolumeFile& file) {
  VolumeFile::Type type = file.type();
  if (int size = file.path_size())
    return file.path(size - 1).c_str();

  if (type == VolumeFile::MUSIC)
    return "<Music>";

  if (type == VolumeFile::USER)
    return "<User>";

  if (type == VolumeFile::VOLUME || type == VolumeFile::CD) {
    string name = file.name();
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

bool compare(const VolumeFile& x, const VolumeFile& y) {
  if (x.type() < y.type())
    return true;

  if (x.type() > y.type())
    return false;

  if (x.name() < y.name())
    return true;

  if (x.name() > y.name())
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

bool operator==(const VolumeFile& x, const VolumeFile& y) {
  return !(compare(x, y) || compare(y, x));
}

AudioFormatReader* createReader(const VolumeFile& file) {
  if (file.type() != VolumeFile::CD)
    return audio::getAudioFormatManager()->createReaderFor(getFile(file));

  if (!file.path_size()) {
    LOG(ERROR) << "Can't create track for root CD volume for "
               << file.DebugString();
    return NULL;
  }

  int track = String(file.path(0).c_str()).getIntValue();
  return util::cd::createCDTrackReader(file.name().c_str(), track);
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
  return !f.has_type();
}

VolumeFile toVolumeFile(const File& file) {
  VolumeFile vf;
  vf.set_type(VolumeFile::VOLUME);

  File f = file, p = file.getParentDirectory();
  for (; f != p; f = p, p = f.getParentDirectory())
    vf.add_path(f.getFileName().toCString());
  string lastName = f.getFileName().toCString();
  if (lastName.size())
    vf.add_path(lastName);


#if JUCE_MAC
  int last = vf.path_size() - 1;
  const string& root = vf.path(last);

  if (root == "Volumes" && last != 0) {
    vf.set_name(vf.path(last - 1));
    vf.mutable_path()->RemoveLast();
    vf.mutable_path()->RemoveLast();
  }

  // TODO: CD things here.
#endif

  for (int i = 0; i < vf.path_size() / 2; ++i)
    vf.mutable_path()->SwapElements(i, vf.path_size() - i - 1);

  return vf;
}

void sort(VolumeFileList* v) {
  std::sort(v->mutable_file()->begin(), v->mutable_file()->end(), compare);
}

}  // namespace file
}  // namespace util
}  // namespace rec
