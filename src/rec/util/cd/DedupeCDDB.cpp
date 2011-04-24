#include "rec/util/cd/DedupeCDDB.h"
#include "rec/music/Metadata.pb.h"

namespace rec {
namespace util {
namespace cd {

string normalize(const string& s) {
  static const char delimiters[] = "[(";

  int length = s.size();
  for (const char* i = delimiters; *i; ++i) {
    int loc = s.find(*i);
    if (loc > 0 && loc < length)
      length = loc;
  }

  int start = 0;
  for (; start < length && isspace(s[start]); ++start);
  for (; start < length && isspace(s[length - 1]); --length);

  string result(s, start, length);
  for (int i = 0; i < result.size(); ++i)
    result[i] = tolower(result[i]);

  return result;
}

bool similar(const Album& x, const Album& y) {
  int size = x.track_size();
  if (!(similar(x.album().artist(), y.album().artist()) &&
        similar(x.album().album_title(), y.album().album_title()) &&
        size == y.track_size()))
    return false;

  for (int i = 0; i < size; ++i) {
    if (!similarTrack(x.track(i), y.track(i)))
      return false;
  }

  return true;
}

bool similar(const string& x, const string& y) {
  return normalize(x) == normalize(y);
}

bool similarTrack(const Metadata& x, const Metadata& y) {
  return similar(x.track_title(), y.track_title());
}

void addIfNotSimilar(AlbumList* albums, const Album& album) {
  for (int i = 0; i < albums->album_size(); ++i) {
    if (similar(album, albums->album(i)))
      return;
  }
  albums->add_album()->CopyFrom(album);
}

}  // namespace cd
}  // namespace util
}  // namespace rec
