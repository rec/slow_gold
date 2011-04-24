#include "rec/audio/source/VirtualFileSource.h"
#include "rec/util/cd/CDReader.h"
#include "rec/audio/util/AudioFormatManager.h"
#include "rec/util/cd/Album.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"

namespace rec {
namespace audio {
namespace source {

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
    String filename = file.name().c_str();
    reader.reset(cd::createCDTrackReader(filename, track));

    if (needsRead) {
      ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename));
      metadata = getTrack(cd::getAlbum(file, cdr->getTrackOffsets()), track);
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

PositionableAudioSource* virtualFileSource(const VirtualFile& file) {
  ptr<AudioFormatReader> reader(createReader(file));
  if (reader)
    return new AudioFormatReaderSource(reader.transfer(), true);
  else
    LOG(ERROR) << "No reader for " << getFullDisplayName(file);
  return NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
