#include "rec/music/CreateMusicFileReader.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/audio/util/AudioFormatManager.h"
#include "rec/music/Metadata.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"

namespace rec {
namespace music {

namespace {

AudioFormatReader* createCDReader(const VirtualFile& file, Metadata* metadata) {
  if (!file.path_size()) {
    LOG(ERROR) << "Can't create track for " << file.DebugString();
    return NULL;
  }

  int track = String(file.path(0).c_str()).getIntValue();
  String filename = str(file.name());
  if (metadata) {
    ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename));
    *metadata = rec::music::getTrack(cd::getCachedAlbum(file, cdr->getTrackOffsets()), track);
  }
  return cd::createCDTrackReader(filename, track);
}

}  // namespace

AudioFormatReader* createMusicFileReader(const VirtualFile& file) {
  if (file::empty(file) || !file.path_size()) {
    LOG(ERROR) << "Can't create track for " << file.DebugString();
    return NULL;
  }

  music::Metadata metadata;
  ptr<AudioFormatReader> reader;
  persist::Data<Metadata>* d = persist::setter<music::Metadata>(file);
  bool fileRead = d->fileReadSuccess();

  if (file.type() == VirtualFile::CD) {
    reader.reset(createCDReader(file, fileRead ? &metadata : NULL));
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


}  // namespace music
}  // namespace rec

