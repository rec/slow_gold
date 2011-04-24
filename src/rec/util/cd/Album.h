#ifndef __REC_UTIL_CD_ALBUM__
#define __REC_UTIL_CD_ALBUM__

#include "rec/base/base.h"
#include "rec/music/Metadata.pb.h"

namespace rec {
namespace util {
namespace cd {

typedef juce::Array<int> TrackOffsets;

music::Album getCachedAlbum(const VirtualFile& file, const TrackOffsets& off);
String fillAlbums(const TrackOffsets& off, music::AlbumList* albums);

music::Metadata getTrack(const music::Album& album, int i);
music::Metadata getMetadata(const StringPairArray& metadata);

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_ALBUM__
