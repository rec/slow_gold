#include "rec/util/cd/DedupeCDDB.h"

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
  int size = x.tracks_.size();
  if (!(similar(x.artist_, y.artist_) &&
        similar(x.title_, y.title_) &&
        size == y.tracks_.size()))
    return false;

  for (int i = 0; i < size; ++i) {
    if (!similar(x.tracks_[i], y.tracks_[i]))
      return false;
  }

  return true;
}

bool similar(const string& x, const string& y) {
  return normalize(x) == normalize(y);
}

bool similar(const Track& x, const Track& y) {
  return similar(x.title(), y.title());
}

string unnull(const char* x) {
  return string(x ? x : "");
}

void addIfNotSimilar(AlbumList* albums, const Album& album) {
  for (int i = 0; i < albums->size(); ++i) {
    if (similar(album, (*albums)[i]))
      return;
  }
  albums->push_back(album);
}

void dedupeAlbums(AlbumList* albums) {
  // This process is quadratic in the number of albums, but we only ever get a
  // handful.
  for (int i = albums->size() - 1; i > 0; --i) {
    for (int j = i - 1; j >= 0; --j) {
      if (similar((*albums)[i], (*albums)[j])) {
        albums->erase(i + albums->begin());
        break;
      }
    }
  }
}

}  // namespace cd
}  // namespace util
}  // namespace rec
