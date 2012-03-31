#include "rec/util/cd/CDReader.h"
#include "rec/music/Metadata.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

// i18n


AudioCDReader* getAudioCDReader(const String& cdKey, String* error) {
  String e;
  if (!error)
    error = &e;

  int id = cdKey.initialSectionNotContaining("-").getHexValue32();
  StringArray names = AudioCDReader::getAvailableCDNames();
  int size = names.size();
  if (!size) {
    (*error) = "No available CDs";
    return NULL;
  }

  for (int i = 0; i < size; ++i) {
    ScopedPointer<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
    if (!reader) {
      LOG(ERROR) << "Couldn't create reader for " << names[i];
      if (error->length())
        *error += ", ";
      *error += names[i];
    } else if (reader->getCDDBId() == id) {
      *error = "";
      return reader.release();
    }
  }
  LOG(ERROR) << "Couldn't find an AudioCDReader for ID " << id;
  (*error) = "Tried to read CD, id=" + String(id) + ", names=" + *error;
  return NULL;
}

AudioFormatReader* createCDTrackReader(AudioCDReader* reader, int track) {
  ptr<AudioCDReader> r(reader);
  int trackIndex = getAudioTrackIndex(*r, track);
  if (trackIndex == -1) {
    LOG(DFATAL) << "No track " << track << " in " << reader->getCDDBId();
    return NULL;
  }

  int begin = r->getPositionOfTrackStart(trackIndex);
  int end = r->getPositionOfTrackStart(trackIndex + 1);
  return new AudioSubsectionReader(r.transfer(), begin, end - begin, true);
}

AudioFormatReader* createCDTrackReader(const String& cdKey, int track) {
  ptr<AudioCDReader> reader(getAudioCDReader(cdKey));
  if (reader)
    return createCDTrackReader(reader.transfer(), track);

  LOG(ERROR) << "Couldn't create reader for " << cdKey;
  return NULL;
}

int getAudioTrackIndex(const AudioCDReader& reader, int audioTrack) {
  for (int i = 0, audioTracks = 0; i < reader.getNumTracks(); ++i) {
    if (reader.isTrackAudio(i) && audioTracks++ == audioTrack)
      return i;
  }
  return -1;
}

int getAudioTrackCount(const AudioCDReader& reader) {
  int audioTracks = 0;
  for (int i = 0; i < reader.getNumTracks(); ++i) {
    if (reader.isTrackAudio(i))
      ++audioTracks;
  }
  return audioTracks;
}

static int64 primes[] = {
  1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
  71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
  157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
  239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
  331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
  421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
  509, 521, 523
};

String getCDKey(AudioCDReader* reader) {
  const Array<int>& offsets = reader->getTrackOffsets();

  int64 r = 0;
  int last = offsets.size() - 1;
  if (last <= 0)
    return "";

  for (int i = 0; i < last; ++i)
    r += (primes[i] * offsets[i] * (reader->isTrackAudio(i) ? 1 : -1));
  r += primes[last] * offsets[last];

  int c = reader->getCDDBId();
  return (c == 0x2000001 || r == 0) ? String("") :
    (String::toHexString(c) + "-" + String::toHexString(r)).toUpperCase();
}

}  // namespace cd
}  // namespace util
}  // namespace rec
