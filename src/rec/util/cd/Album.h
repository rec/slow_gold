#ifndef __REC_UTIL_CD_ALBUM__
#define __REC_UTIL_CD_ALBUM__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

class Album;
class AlbumList;

void splitTitle(Album *album);
void splitTracks(Album* album);
void fillAlbum(const StringPairArray& cd, Album* album);
StringPairArray parseCDData(const StringArray& cds);
void fillAlbumList(Socket* sock, const TrackOffsets& off, AlbumList* albums);
String fillAlbumList(const TrackOffsets& off, AlbumList* albums);


}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_ALBUM__
