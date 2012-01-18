#include "rec/music/Metadata.h"

#include "rec/audio/format/mpg123/CleanGenre.h"
#include "rec/util/file/VirtualFile.pb.h"

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
    else if (k == "TCON") t.set_genre(audio::format::mpg123::cleanGenre(v));
    else if (k == "TDRC") t.set_year(v);
    else if (k == "TIT2") t.set_track_title(v);
    else if (k == "TPE1") t.set_artist(v);
    else if (k == "TPE2") t.set_artist(v);  // TODO: difference?!
    else if (k == "TRCK") t.set_track_number(v);
  }
  return t;
}

string getTitle(const Metadata& md) {
  string result;

  if (md.has_track_title())
    result = "\"" + md.track_title() + "\"";

  if (md.has_album_title()) {
    if (result.empty())
      result = md.album_title();
    else
      result += " - " + md.album_title();
  }

  if (md.has_artist() && !result.empty())
    result += " (" + md.artist() + ")";

  return result;
}

string getTitle(const VirtualFile& f) {
  string result;
  if (f.path_size())
    result = f.path(f.path_size() - 1);
  return result;
}

string getTitle(const File& f) {
  return str(f.getFileName());
}

}  // namespace music
}  // namespace rec

