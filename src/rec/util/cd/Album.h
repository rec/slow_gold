#ifndef __REC_UTIL_CD_ALBUM__
#define __REC_UTIL_CD_ALBUM__

#include "rec/base/base.h"


namespace rec {
namespace util {
namespace cd {

class Album;
class AlbumList;
typedef juce::Array<int> TrackOffsets;

void splitTitle(Album *album);
void splitTracks(Album* album);
void addAlbumValue(const String& key, const string& value, Album* album);
void fillAlbum(const StringArray& cds, int tracks, Album* album);
void fillAlbumList(Socket* sock, const TrackOffsets& off, AlbumList* albums);
String fillAlbums(const TrackOffsets& off, AlbumList* albums);


}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_ALBUM__
