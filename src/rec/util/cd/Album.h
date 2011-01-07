#ifndef __REC_UTIL_CD_ALBUM__
#define __REC_UTIL_CD_ALBUM__

#include "rec/base/base.h"
#include "rec/util/cd/Album.pb.h"

namespace rec {
namespace util {
namespace cd {

typedef juce::Array<int> TrackOffsets;

void splitTitle(Album *album);
void splitTracks(Album* album);
void addAlbumValue(const String& key, const string& value, Album* album);
void fillAlbum(const StringArray& cds, int tracks, Album* album);
void fillAlbumList(Socket* sock, const TrackOffsets& off, AlbumList* albums);
String fillAlbums(const TrackOffsets& off, AlbumList* albums);

Metadata getTrack(const Album& album, int i);
Album getAlbum(const VolumeFile& file, const TrackOffsets& off);
Metadata getMetadata(const StringPairArray& metadata);

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_ALBUM__
