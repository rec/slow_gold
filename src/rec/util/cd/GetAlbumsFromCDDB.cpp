#if JUCE_MAC

#include <ctype.h>
#include <string.h>

#include <vector>

#include <cddb/cddb.h>

#include "rec/util/cd/GetAlbumsFromCDDB.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace cd {

namespace {

// static const int SAMPLES_PER_SECOND = AudioCDReader::samplesPerFrame *
//  AudioCDReader::framesPerSecond;
// const int FRAMES_PER_SECOND = 75;

const int SAMPLES_PER_SECOND = 44100;
const int SAMPLES_PER_FRAME = 44100 / FRAMES_PER_SECOND;

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

bool similar(const string& x, const string& y) {
  return normalize(x) == normalize(y);
}

bool similar(const Track& x, const Track& y) {
  return similar(x.title_, y.title_);
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

inline string unnull(const char* x) {
  return string(x ? x : "");
}

Track fillTrack(cddb_track_t* track) {
  Track t;
  t.length_ = cddb_track_get_length(track);
  t.frameOffset_ = cddb_track_get_frame_offset(track);
  t.title_ = unnull(cddb_track_get_title(track));
  t.artist_ = unnull(cddb_track_get_artist(track));
  t.extdata_ = unnull(cddb_track_get_ext_data(track));

  return t;
}

Album fillAlbum(cddb_disc_t* disc) {
  Album album;

  album.discid_ = cddb_disc_get_discid(disc);
  album.length_ = cddb_disc_get_length(disc);
  album.revision_ = cddb_disc_get_revision(disc);
  album.year_ = cddb_disc_get_year(disc);
  album.category_ = unnull(cddb_disc_get_category_str(disc));
  album.genre_ = unnull(cddb_disc_get_genre(disc));
  album.title_ = unnull(cddb_disc_get_title(disc));
  album.artist_ = unnull(cddb_disc_get_artist(disc));
  album.extdata_ = unnull(cddb_disc_get_ext_data(disc));

  int trackCount = cddb_disc_get_track_count(disc);
  for (int i = 0; i < trackCount; ++i)
    album.tracks_.push_back(fillTrack(cddb_disc_get_track(disc, i)));

  return album;
}

void addIfNotSimilar(std::vector<Album>* albums, const Album& album) {
  for (int i = 0; i < albums->size(); ++i) {
    if (similar(album, (*albums)[i]))
      return;
  }
  albums->push_back(album);
}

}  // namespace

string getAlbumsFromCDDB(const std::vector<int>& offsets, std::vector<Album>* albums) {
  string error;
  cddb_conn_t *conn = cddb_new();
  cddb_disc_t *disc = cddb_disc_new();

  int trackCount = offsets.size() - 1;

  int length = (offsets[trackCount] - offsets[0]) / SAMPLES_PER_SECOND;
  cddb_disc_set_length(disc, length);

  for (int i = 0; i < trackCount; ++i) {
    cddb_track_t *track = cddb_track_new();
    cddb_disc_add_track(disc, track);
    cddb_track_set_frame_offset(track, offsets[i] / SAMPLES_PER_FRAME);
  }

  int matches = cddb_query(conn, disc);
  if (matches <= 0) {
    if (cddb_error_t e = cddb_errno(conn))
      error = cddb_error_str(e);
    else
      error = "No matches for this disc";

  } else {
    for (; matches; --matches && cddb_query_next(conn, disc)) {
      if (!cddb_read(conn, disc))
        error = cddb_error_str(cddb_errno(conn));
      else
        albums->push_back(fillAlbum(disc));
    }
  }

  cddb_disc_destroy(disc);
  cddb_destroy(conn);
  return error;
}

void dedupeAlbums(std::vector<Album>* albums) {
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
}  // namespace rec

#endif  // JUCE_MAC
