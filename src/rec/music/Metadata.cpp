#include "rec/music/Metadata.h"

#include "rec/audio/format/mpg123/CleanGenre.h"
#include "rec/music/Metadata.pb.h"

namespace rec {
namespace music {

Metadata getTrack(const Album& album, int i) {
  Metadata track = album.album();
  if (i >= 0 && i < album.track_size())
    track.MergeFrom(album.track(i));

  return track;
}

Metadata getMetadata(const StringPairArray& metadata) {
  Metadata t;
  const StringArray& keys = metadata.getAllKeys();
  for (int i = 0; i < keys.size(); ++i) {
    const String& k = keys[i];
    const string& v = str(metadata[k]);

    if (k < "TALB" || k > "TRCK") continue;
    else if (k == "TALB") t.set_album_title(v);
    else if (k == "TCON") t.set_genre(audio::format::mp3::cleanGenre(v));
    else if (k == "TDRC") t.set_year(v);
    else if (k == "TIT2") t.set_track_title(v);
    else if (k == "TPE1") t.set_artist(v);
    else if (k == "TPE2") t.set_artist(v);  // TODO: difference?!
    else if (k == "TRCK") t.set_track_number(v);
  }
  return t;
}

}  // namespace music
}  // namespace rec

