#include "rec/music/CreateMusicFileReader.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/audio/util/AudioFormatManager.h"
#include "rec/music/Metadata.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Value.h"

namespace rec {
namespace music {

namespace {

AudioFormatReader* createCDReader(const VirtualFile& file, Metadata* metadata) {
  int track = String(file.path(0).c_str()).getIntValue();
  String filename = str(file.name());
  if (metadata) {
    ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename));
    *metadata = rec::music::getTrack(cd::getCachedAlbum(file, cdr->getTrackOffsets()), track);
  }
  return cd::createCDTrackReader(filename, track);
}

AudioFormatReader* createFileReader(const VirtualFile& file, Metadata* metadata) {
  ptr<AudioFormatReader> reader(audio::createReader(file));
  if (metadata)
    *metadata = music::getMetadata(reader->metadataValues);

  return reader.transfer();
}

}  // namespace

AudioFormatReader* createMusicFileReader(const VirtualFile& file) {
  if (file::empty(file) || !file.path_size()) {
    LOG(ERROR) << "Can't create track for " << file.DebugString();
    return NULL;
  }

  ptr<Metadata> metadata;
  persist::TypedEditable<Metadata>* d = persist::editable<music::Metadata>(file);
  if (d->fileReadSuccess())
    metadata.reset(new Metadata);

  ptr<AudioFormatReader> reader;
  if (file.type() == VirtualFile::CD)
    reader.reset(createCDReader(file, metadata.get()));
  else
    reader.reset(createFileReader(file, metadata.get()));

  if (!reader) {
    LOG(ERROR) << "Couldn't create reader for file " << file.ShortDebugString();
    return NULL;
  }

  if (metadata && (*metadata != music::Metadata::default_instance()))
    d->set(*metadata);

  return reader.transfer();
}


}  // namespace music
}  // namespace rec

