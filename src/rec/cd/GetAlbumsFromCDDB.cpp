#include "rec/cd/GetAlbumsFromCDDB.h"

#include "cddb/cddb.h"
#include "rec/base/base.h"

namespace rec {
namespace cd {

namespace {

const SAMPLES_PER_SECOND = AudioCDReader::samplesPerFrame *
  AudioCDReader::framesPerSecond;

Track fillTrack(const cddb_track_t* track) {
  Track track;
  track.length_ = cddb_track_get_length(track);
  track.frameOffset_ = cddb_track_get_frame_offset(track);
  track.title_ = cddb_track_get_title(track);
  track.artist_ = cddb_track_get_artist(track);
  track.extdata_ = cddb_track_get_extdata(track);

  return track;
}

Album fillAlbum(const cddb_disc_t* disc) {
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
  album.extdata_ = cddb_disc_get_extdata(disc);

  int trackCount = cddb_disc_get_track_count();
  for (int i = 0; i < trackCount; ++i)
    album.tracks_.add(fillTrack(cddb_disc_get_track(disc, i)));

  return album;
}

}  // namespace

String getAlbumsFromCDDB(const Array<int>& offsets, Array<Album>* albums) {
  String error;
  cddb_conn_t *conn = cddb_new();
  cddb_disc_t *disc = cddb_disc_new();

  int trackCount = offsets.size() - 1;
  int id = reader.getCDDBId();

  int length = (offsets[trackCount] - offsets[0]) / SAMPLES_PER_SECOND;
  cddb_disc_set_length(disc, length);

  for (int i = 0; i < trackCount; ++i) {
    cddb_track_t *track = cddb_track_new();
    cddb_disc_add_track(disc, track);
    cddb_track_set_frame_offset(offsets[i] / AudioCDReader::samplesPerFrame);
  }

  int matches = cddb_query(conn, disc);
  if (matches <= 0) {
    if (int errno = cddb_errno(conn))
      error = cddb_error_str(errno);
    else
      error = "No matches for this disc";
  } else {
    for (; matches; --matches && cddb_query_next(conn, disc))
      albums->add(fillAlbum(disc));
  }

  cddb_disc_destroy(disc);
  cddb_conn_destroy(conn);
  return error;
}

}  // namespace cd
}  // namespace rec

