#include "rec/music/CreateMusicFileReader.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/audio/format/AudioFormatManager.h"
#include "rec/music/Metadata.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Value.h"

namespace rec {
namespace music {

namespace {

using namespace rec::audio::format;

AudioFormatReader* createCDReader(const VirtualFile& file, Metadata* metadata) {
  int track = String(file.path(0).c_str()).getIntValue();
  String filename = str(file.volume_name());
  if (metadata) {
    ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename));
    if (cdr)
      *metadata = rec::music::getTrack(cd::getCachedAlbum(file, cdr->getTrackOffsets()), track);
  }
  return cd::createCDTrackReader(filename, track);
}

AudioFormatReader* createFileReader(const VirtualFile& file, Metadata* metadata) {
  ptr<AudioFormatReader> reader(createReader(getRealFile(file)));
  if (metadata && reader)
    *metadata = music::getMetadata(reader->metadataValues);

  return reader.transfer();
}

}  // namespace

AudioFormatReader* createMusicFileReader(const VirtualFile& file) {
  if (file::empty(file) || !file.path_size()) {
    LOG(DFATAL) << "Can't create track for " << file.ShortDebugString();
    return NULL;
  }

  ptr<Metadata> metadata;
  data::Data* d = data::getData<music::Metadata>(&file);
  if (!d->fileReadSuccess())
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
    data::setWithData(d, *metadata, CANT_UNDO);

  return reader.transfer();
}


}  // namespace music
}  // namespace rec

