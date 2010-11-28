#ifndef __REC_CD_GETALBUMSFROMCDDB__
#define __REC_CD_GETALBUMSFROMCDDB__

#include <vector>
#include "rec/base/base.h"

namespace rec {
namespace cd {

struct Track {
  int length_;
  int frameOffset_;

  string title_;
  string artist_;
  string extdata_;
};

typedef std::vector<Track> TrackList;

struct Album {
  int discid_;
  int length_;
  int revision_;
  int year_;

  string category_;
  string genre_;
  string title_;
  string artist_;
  string extdata_;

  TrackList tracks_;
};

typedef std::vector<int> TrackOffsets;
typedef std::vector<Album> AlbumList;

// Fill a list of albums from the CDDB.  Return an error message or the empty
// string if there was no error.
string getAlbumsFromCDDB(const TrackOffsets& offsets, AlbumList* albums);


// Remove any albums that are similar to another album in the list.
void dedupeAlbums(AlbumList* albums);

}  // namespace cd
}  // namespace rec

#endif  // __REC_CD_GETALBUMSFROMCDDB__
