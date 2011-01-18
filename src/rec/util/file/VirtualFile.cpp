#include <algorithm>

#include "rec/util/file/VirtualFile.h"

#include "rec/audio/AudioFormatManager.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/util/file/Util.h"

using namespace juce;
using namespace google;

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

const File getVirtual(const VirtualFile& v) {
  if (v.type() == VirtualFile::CD) {
    CHECK(v.type() != VirtualFile::CD);
  }

  if (v.type() == VirtualFile::MUSIC) {
    DCHECK_EQ(v.name(), "");
    return File::getSpecialLocation(File::userMusicDirectory);
  }

  if (v.type() == VirtualFile::VOLUME) {
#if JUCE_MAC
    if (v.name().empty())
      return File("/");
#else
    DCHECK(!v.name().empty());
#endif
    return File(v.name().c_str());
  }

  if (v.type() == VirtualFile::USER) {
    DCHECK_EQ(v.name(), "");
    return File::getSpecialLocation(File::userHomeDirectory);
  }

  CHECK(false) << v.type();
  return File();
}

const File getShadowDirectory(const VirtualFile& vf) {
  String name = String(VirtualFile::Type_Name(vf.type()).c_str()).toLowerCase();
  File f = persist::getApp()->appDir().getChildFile(name);
  return getFile(getFile(f, vf.name()), vf.path());
}

const File getFile(const VirtualFile& file) {
  return getFile(getVirtual(file), file.path());
}

const String getFilename(const VirtualFile& file) {
  return file.path_size() ? file.path().end()[-1].c_str() : "<none>";
}

const String getDisplayName(const VirtualFile& file) {
  VirtualFile::Type type = file.type();
  if (int size = file.path_size())
    return file.path(size - 1).c_str();

  if (type == VirtualFile::MUSIC)
    return "<Music>";

  if (type == VirtualFile::USER)
    return "<User>";

  if (type == VirtualFile::VOLUME || type == VirtualFile::CD) {
    string name = file.name();
    eraseVolumePrefix(&name, false);
    return name.empty() ? "<Root>" : name.c_str();
  }

  return "<Unknown Virtual>";
}

const String getFullDisplayName(const VirtualFile& file) {
  String result = getDisplayName(file) + ":";
  for (int i = 0; i < file.path_size(); ++i)
    result += (file.path(i) + "/").c_str();
  return result;
}

bool compare(const VirtualFile& x, const VirtualFile& y) {
  if (x.type() < y.type())
    return true;

  if (x.type() > y.type())
    return false;

  if (x.name() < y.name())
    return true;

  if (x.name() > y.name())
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
  return false;
}

namespace {

AudioFormatReader* createReader(const VirtualFile& file) {
  cd::Metadata metadata;
  ptr<AudioFormatReader> reader;
  persist::Data<cd::Metadata>* data = persist::data<cd::Metadata>(file);
  bool needsRead = !data->fileReadSuccess();

  if (file.type() == VirtualFile::CD) {
    if (!file.path_size()) {
      LOG(ERROR) << "Can't create track for root CD volume for "
                 << file.DebugString();
      return NULL;
    }

    int track = String(file.path(0).c_str()).getIntValue();
    reader.reset(util::cd::createCDTrackReader(file.name().c_str(), track));

    if (needsRead) {
      const cd::TrackOffsets& off = dynamic_cast<AudioCDReader*>(
          reader.get())->getTrackOffsets();
      metadata = getTrack(cd::getAlbum(file, off), track);
          }
  } else {
    reader.reset(audio::getAudioFormatManager()->createReaderFor(getFile(file)));
    if (!reader) {
      LOG(ERROR) << "Couldn't create reader for file " << file.ShortDebugString();
      return NULL;
    }

    if (needsRead)
      metadata = cd::getMetadata(reader->metadataValues);
  }

  if (needsRead && (metadata != cd::Metadata::default_instance()))
    data->set(metadata);

  return reader.transfer();
}

}  // namespace

PositionableAudioSource* createSource(const VirtualFile& file) {
  ptr<AudioFormatReader> reader(createReader(file));
  if (reader)
    return new AudioFormatReaderSource(reader.transfer(), true);
  else
    LOG(ERROR) << "No reader for " << getFullDisplayName(file).toCString();
  return NULL;
}

bool empty(const VirtualFile& f) {
  return !f.has_type();
}

VirtualFile toVirtualFile(const File& file) {
  VirtualFile vf;
  vf.set_type(VirtualFile::VOLUME);

  File f = file, p = file.getParentDirectory();
  for (; f != p; f = p, p = f.getParentDirectory())
    vf.add_path(f.getFileName().toCString());
  string lastName = f.getFileName().toCString();
  if (lastName.size())
    vf.add_path(lastName);


#if JUCE_MAC
  int last = vf.path_size() - 1;
  const string& root = vf.path(last);

  if (root == "Virtuals" && last != 0) {
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

void sort(VirtualFileList* v) {
  std::sort(v->mutable_file()->begin(), v->mutable_file()->end(), compare);
}

}  // namespace file
}  // namespace util
}  // namespace rec
