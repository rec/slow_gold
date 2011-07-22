#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/audio/util/AudioFormatManager.h"
#include "rec/music/Metadata.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"

namespace rec {
namespace audio {
namespace source {

namespace {

typedef persist::Data<music::Metadata> Data;

}  // namespace

AudioFormatReader* createReaderAndLoadMetadata(const VirtualFile& file) {
  if (file::empty(file))
    return NULL;

  music::Metadata metadata;
  ptr<AudioFormatReader> reader;
  persist::Data<music::Metadata>* d = persist::setter<music::Metadata>(file);
  bool fileRead = d->fileReadSuccess();

  if (file.type() == VirtualFile::CD) {
    if (!file.path_size()) {
      LOG(ERROR) << "Can't create track for " << file.DebugString();
      return NULL;
    }

    int track = String(file.path(0).c_str()).getIntValue();
    String filename = str(file.name());
    reader.reset(cd::createCDTrackReader(filename, track));

    if (!fileRead) {
      ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename));
      metadata = rec::music::getTrack(cd::getCachedAlbum(file, cdr->getTrackOffsets()), track);
    }
  } else {
    reader.reset(audio::createReader(file));
    if (!reader) {
      LOG(ERROR) << "Couldn't create reader for file " << file.ShortDebugString();
      return NULL;
    }

    if (!fileRead)
      metadata = music::getMetadata(reader->metadataValues);
  }

  if (!fileRead && (metadata != music::Metadata::default_instance()))
    data::set(d, metadata);

  return reader.transfer();
}

PositionableAudioSource* createSourceAndLoadMetadata(const VirtualFile& file) {
  if (!empty(file)) {
    ptr<AudioFormatReader> reader(createReaderAndLoadMetadata(file));
    if (reader)
      return new AudioFormatReaderSource(reader.transfer(), true);
    LOG(ERROR) << "No reader for " << getFullDisplayName(file);
  }

  return NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

