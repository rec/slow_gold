#ifndef __REC_UTIL_CD_DEDUPECDDB__
#define __REC_UTIL_CD_DEDUPECDDB__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

class Album;
class AlbumList;
class Metadata;

string normalize(const string& s);

bool similar(const string& x, const string& y);
bool similarTrack(const Metadata& x, const Metadata& y);
bool similar(const Album& x, const Album& y);

void addIfNotSimilar(AlbumList* albums, const Album& album);

#if 0
// Remove any albums that are similar to another album in the list.
void dedupeAlbums(AlbumList* albums);
#endif

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_DEDUPECDDB__
