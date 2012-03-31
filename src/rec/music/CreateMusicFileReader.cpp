#include "rec/music/CreateMusicFileReader.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/audio/format/Manager.h"
#include "rec/music/Metadata.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Value.h"

namespace rec {
namespace music {

namespace {

// i18n

const int MINIMUM_FILE_SIZE = 5 * 44100;

using namespace rec::audio::format;

AudioFormatReader* createCDReader(const VirtualFile& file, Metadata* metadata,
                                  String* error) {
  int track = String(file.path(0).c_str()).getIntValue() - 1;
  String filename = str(file.volume_name());
  if (metadata) {
    ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename, error));
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

MusicFileReader::MusicFileReader(const VirtualFile& file) {
  if (file::empty(file) || !file.path_size()) {
    errorTitle_ = "Can't create track for " + str(file.ShortDebugString());
    errorDetails_ = errorTitle_;
    LOG(DFATAL) << errorTitle_;
    return;
  }

  ptr<Metadata> metadata;
  data::Data* d = data::getData<Metadata>(&file);
  if (!d->fileReadSuccess())
    metadata.reset(new Metadata);

  ptr<AudioFormatReader> reader;
  if (file.type() == VirtualFile::CD) {
    String error;
    reader_.reset(createCDReader(file, metadata.get(), &error));
    if (!reader_) {
      errorTitle_ = "Couldn't Open CD Track.";
      errorDetails_ = "Couldn't open track on CD - perhaps you ejected it?\n"
        "Error was: " + error;
    }
  } else {
    File f = getRealFile(file);
    if (!f.existsAsFile()) {
      errorTitle_ = "File Does Not Exist";
      errorDetails_ = "Sorry, file " + file::getFullDisplayName(file) +
        " does not exist.";
    } else {
      reader_.reset(createFileReader(file, metadata.get()));

      if (!reader) {
#if JUCE_WINDOWS
        if (f.getFileExtension() == ".m4a") {
          errorTitle_ = "We Can't Read .m4a Files On Windows";
          errorDetails_ = "Sorry, file " + file::getFullDisplayName(file) +
            " is an .m4a file and we can't yet read these files on Windows: "
            " please convert it to mp3 using iTunes.";
        } else {
#endif
          errorTitle_ = "Couldn't Open Your File.";
          errorDetails_ = "Sorry, the program couldn't open your file " +
            file::getFullDisplayName(file) +
            ".\nEither it wasn't in the right format, it's corrupted, or "
            "the programmer made a mistake.";
#if JUCE_WINDOWS
        }
#endif
      }
    }
  }

  if (reader_) {
    int64 length = reader_->lengthInSamples;
    if (!length) {
      errorTitle_ = "Your File Was Empty.";
      errorDetails_ = "Sorry, the file you tried to open, " +
        file::getFullDisplayName(file) +
            " has a length of zero.";
      reader_.reset();
    } else if (length < MINIMUM_FILE_SIZE) {
      errorTitle_ = "Your File Was Too Small.";
      errorDetails_ = "Sorry, the file you tried to open, " +
        file::getFullDisplayName(file) +
            " has a length of less than five seconds.";
      reader_.reset();
    }
  }

  if (reader_ && metadata && (*metadata != music::Metadata::default_instance()))
    data::setWithData(d, *metadata, CANT_UNDO);
}


}  // namespace music
}  // namespace rec

