#include "rec/music/CreateMusicFileReader.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/cd/Album.h"
#include "rec/audio/Audio.h"
#include "rec/audio/format/Manager.h"
#include "rec/base/Trans.h"
#include "rec/music/Metadata.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Value.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/file/DisplayFile.h"

namespace rec {
namespace music {

TRTR(FILE_TOO_SMALL, "Your File Was Too Small.");
TRTR(FILE_TOO_SMALL_FULL, "Sorry, the file you tried to %s"
                          " has a length of less than one second.");

namespace {

TRTR(CANT_CREATE_TRACK, "Can't create track for %s.");
TRTR(COULDNT_OPEN_TRACK, "Couldn't Open CD Track.");
TRTR(COULDNT_OPEN_TRACK_FULL, "Couldn't open track on CD - perhaps you ejected it?");
TRTR(ERROR_WAS, "Error was");
TRTR(FILE_NOT_EXIST, "Can't Find File");
TRTR(FILE_NOT_EXIST_FULL, "Sorry, we couldn't find the file %s.  Perhaps you "
                          "deleted it, or perhaps it's on a drive that isn't "
                          "currently mounted.");
TRTR(THE_FULL_PATH, "The full path was: %s");
TRTR(CANT_READ_M4A, "We Can't Read .m4a Files On Windows");
TRTR(CANT_READ_M4A_FULL, "Sorry, file %s is an .m4a file and we can't yet "
                         "read these files on Windows: "
                         " please convert it to mp3 using iTunes.");

TRTR(COULDNT_OPEN_FILE, "Couldn't Open Your File.");
TRTR(COULDNT_OPEN_FILE_FULL, "Sorry, the program couldn't open your file %s.");
TRTR(WRONG_FORMAT, "Either it wasn't in the right format, it's corrupted, or "
                   "the programmer made a mistake.");

TRTR(EMPTY_FILE, "Your File Was Empty.");
TRTR(EMPTY_FILE_FULL, "Sorry, the file you tried to open, %s "
                      "has a length of zero.");

using namespace rec::audio::format;

AudioFormatReader* createCDReader(const VirtualFile& file, Metadata* metadata,
                                  String* error) {
  int track = String(file.path(0).c_str()).getIntValue() - 1;
  String filename = str(file.volume_name());
  if (metadata) {
    ptr<AudioCDReader> cdr(cd::getAudioCDReader(filename, error));
    if (cdr) {
      Album album = cd::getCachedAlbum(file, cdr->getTrackOffsets());
      *metadata = rec::music::getTrack(album, track);
    }
  }

  return cd::createCDTrackReader(filename, track);
}

AudioFormatReader* createFileReader(const VirtualFile& file, Metadata* metadata) {
  ptr<AudioFormatReader> reader(createReader(toRealFile(file)));
  if (metadata && reader)
    *metadata = music::getMetadata(reader->metadataValues);

  return reader.transfer();
}

}  // namespace

MusicFileReader::MusicFileReader(const VirtualFile& file) {
  if (!file.path_size()) {
    errorTitle_ = String::formatted(CANT_CREATE_TRACK,
                                    file.ShortDebugString().c_str());
    errorDetails_ = errorTitle_;
    LOG(DFATAL) << errorTitle_;
    return;
  }

  ptr<Metadata> metadata;
  data::Data* d = data::getData<Metadata>(file);
  if (!d->fileReadSuccess())
    metadata.reset(new Metadata);

  ptr<AudioFormatReader> reader;
  if (file.type() == VirtualFile::CD) {
    String error;
    reader_.reset(createCDReader(file, metadata.get(), &error));
    if (!reader_) {
      errorTitle_ = COULDNT_OPEN_TRACK;
      errorDetails_ = str(COULDNT_OPEN_TRACK_FULL + "\n" + ERROR_WAS + ": "
                          + error);
    }
  } else {
    File f = toRealFile(file);
    if (!f.existsAsFile()) {
      errorTitle_ = FILE_NOT_EXIST;
      errorDetails_ = String::formatted(
          FILE_NOT_EXIST_FULL + String("\n") + THE_FULL_PATH,
          c_str(file::getFilename(file)),
          c_str(file::getFullDisplayName(file)));
    } else {
      reader_.reset(createFileReader(file, metadata.get()));

      if (!reader) {
#if JUCE_WINDOWS
        if (f.getFileExtension() == ".m4a") {
          errorTitle_ = CANT_READ_M4A;
          errorDetails_ = String::formatted(
              CANT_READ_M4A_FULL,
              c_str(file::getFullDisplayName(file)));
        } else {
#endif
          errorTitle_ = COULDNT_OPEN_FILE;
          errorDetails_ = String::formatted(
              COULDNT_OPEN_FILE_FULL,
              c_str(file::getFullDisplayName(file))) + "\n" + WRONG_FORMAT;

#if JUCE_WINDOWS
        }
#endif
      }
    }
  }

  if (reader_) {
    int64 length = reader_->lengthInSamples;
    if (!length) {
      errorTitle_ = EMPTY_FILE;
      errorDetails_ = String::formatted(EMPTY_FILE_FULL,
                                        c_str(file::getFullDisplayName(file)));
      reader_.reset();
    } else if (length < SampleTime(audio::MINIMUM_FILE_SIZE,
                                   reader_->sampleRate)) {
      errorTitle_ = FILE_TOO_SMALL;
      String msg = "open, " + file::getFullDisplayName(file) + ", ";
      errorDetails_ = String::formatted(FILE_TOO_SMALL_FULL, c_str(msg));
      reader_.reset();
    }
  }

  if (reader_ && metadata && (*metadata != music::Metadata::default_instance()))
    data::setProto(*metadata, d, CANT_UNDO);
}

void MusicFileReader::registerAllTranslations() {
  CANT_CREATE_TRACK.registerTranslation();
  COULDNT_OPEN_TRACK.registerTranslation();
  COULDNT_OPEN_TRACK_FULL.registerTranslation();
  ERROR_WAS.registerTranslation();
  FILE_NOT_EXIST.registerTranslation();
  FILE_NOT_EXIST_FULL.registerTranslation();
  THE_FULL_PATH.registerTranslation();
  CANT_READ_M4A.registerTranslation();
  CANT_READ_M4A_FULL.registerTranslation();
  COULDNT_OPEN_FILE.registerTranslation();
  COULDNT_OPEN_FILE_FULL.registerTranslation();
  WRONG_FORMAT.registerTranslation();
  EMPTY_FILE.registerTranslation();
  EMPTY_FILE_FULL.registerTranslation();
  FILE_TOO_SMALL.registerTranslation();
  FILE_TOO_SMALL_FULL.registerTranslation();
}

}  // namespace music
}  // namespace rec
