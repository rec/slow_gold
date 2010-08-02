#include "rec/cd/GetAlbumsFromCDDB.h"

#include "cddb/cddb.h"
#include "rec/base/base.h"

namespace rec {
namespace cd {

namespace {

static const int SAMPLES_PER_SECOND = AudioCDReader::samplesPerFrame *
  AudioCDReader::framesPerSecond;

String normalize(const String& s) {
  static const char* const delimiters = "[(";
  int length = s.length();
  for (const char* i = delimiters; *i; ++i)
    length = jmin(length, s.indexOfChar(*i));

  return s.substring(0, length).trim().toLowerCase();
}

bool similar(const String& x, const String& y) {
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

Track fillTrack(cddb_track_t* track) {
  Track t;
  t.length_ = cddb_track_get_length(track);
  t.frameOffset_ = cddb_track_get_frame_offset(track);
  t.title_ = cddb_track_get_title(track);
  t.artist_ = cddb_track_get_artist(track);
  t.extdata_ = cddb_track_get_ext_data(track);

  return t;
}

Album fillAlbum(cddb_disc_t* disc) {
  Album album;

  album.discid_ = cddb_disc_get_discid(disc);
  album.category_ = cddb_disc_get_category_str(disc);
  album.genre_ = cddb_disc_get_genre(disc);
  album.length_ = cddb_disc_get_length(disc);
  album.revision_ = cddb_disc_get_revision(disc);
  album.year_ = cddb_disc_get_year(disc);
  album.revision_ = cddb_disc_get_revision(disc);
  album.title_ = cddb_disc_get_title(disc);
  album.artist_ = cddb_disc_get_artist(disc);
  album.extdata_ = cddb_disc_get_ext_data(disc);

  int trackCount = cddb_disc_get_track_count(disc);
  for (int i = 0; i < trackCount; ++i)
    album.tracks_.add(fillTrack(cddb_disc_get_track(disc, i)));

  return album;
}

void addIfNotSimilar(Array<Album>* albums, const Album& album) {
  for (int i = 0; i < albums->size(); ++i) {
    if (similar(album, (*albums)[i]))
      return;
  }
  albums->add(album);
}

}  // namespace

String getAlbumsFromCDDB(const Array<int>& offsets, Array<Album>* albums) {
  String error;
  cddb_conn_t *conn = cddb_new();
  cddb_disc_t *disc = cddb_disc_new();

  int trackCount = offsets.size() - 1;

  int length = (offsets[trackCount] - offsets[0]) / SAMPLES_PER_SECOND;
  cddb_disc_set_length(disc, length);

  for (int i = 0; i < trackCount; ++i) {
    cddb_track_t *track = cddb_track_new();
    cddb_disc_add_track(disc, track);
    cddb_track_set_frame_offset(track, offsets[i] / AudioCDReader::samplesPerFrame);
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
        albums->add(fillAlbum(disc));
    }
  }

  cddb_disc_destroy(disc);
  cddb_destroy(conn);
  return error;
}

void dedupeAlbums(Array<Album>* albums) {
  // This process is quadratic in the number of albums, but we only ever get a
  // handful.
  for (int i = albums->size() - 1; i > 0; --i) {
    for (int j = i - 1; j >= 0; --j) {
      if (similar((*albums)[i], (*albums)[j])) {
        albums->remove(i);
        break;
      }
    }
  }
}

}  // namespace cd
}  // namespace rec

