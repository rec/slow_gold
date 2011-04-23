#ifndef __REC_UTIL_CD_ALBUM__
#define __REC_UTIL_CD_ALBUM__

#include "rec/base/base.h"
#include "rec/util/cd/Album.pb.h"

namespace rec {
namespace util {
namespace cd {

typedef juce::Array<int> TrackOffsets;

Album getAlbum(const VirtualFile& file, const TrackOffsets& off);
String fillAlbums(const TrackOffsets& off, AlbumList* albums);

Metadata getTrack(const Album& album, int i);
Metadata getMetadata(const StringPairArray& metadata);

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_ALBUM__
