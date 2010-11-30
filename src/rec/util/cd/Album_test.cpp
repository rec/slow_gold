#include <gtest/gtest.h>

#include "rec/base/ArraySize.h"
#include "rec/util/cd/Album.h"
#include "rec/util/cd/Album.pb.h"

namespace rec {
namespace cd {

TEST(CD, Albums) {
  static const int SPF = 44100 / 75;

  static int trackLengths[] = {
      183 * SPF,
      15240 * SPF,
      28113 * SPF,
      44215 * SPF,
      61385 * SPF,
      80298 * SPF,
      99478 * SPF,
      114173 * SPF,
      126925 * SPF,
      130820 * SPF,
      144218 * SPF,
      168953 * SPF
  };

  static const char* trackNames[] = {
    "Babooshka",
    "Delius (Song Of Summer)",
    "Blow Away (For Bill)",
    "All We Ever Look For",
    "Egypt",
    "The Wedding List",
    "Violin",
    "The Infant Kiss",
    "Night Scented Stock",
    "Army Dreamers",
    "Breathing",
  };

  static int trackCount = arraysize(trackLengths) - 1;

  TrackOffsets offsets(trackLengths, trackLengths + arraysize(trackLengths));
  AlbumList albums;
  EXPECT_EQ(fillAlbumList(offsets, &albums), "");
  EXPECT_EQ(albums.size(), 3);

  for (int i = 0; i < albums.size(); ++i) {
    const Album& album = albums[i];
    EXPECT_NE(album.title_.find("Never For Ever"), -1);
    // EXPECT_STREQ(album.title_.toCString(), "Never For Ever");
    EXPECT_EQ(album.year_, 1980);
    EXPECT_EQ(album.artist_, "Kate Bush");
    EXPECT_EQ(album.tracks_.size(), trackCount);

    for (int j = 0; j < trackCount; ++j)
      EXPECT_EQ(trackNames[j], album.tracks_[j].title_);
  }

  dedupeAlbums(&albums);
  EXPECT_EQ(albums.size(), 1);
}

}  // namespace rec
}  // namespace cd
