#include "rec/util/cd/Album.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Copy.h"
#include "rec/util/Exception.h"
#include "rec/util/cd/CDDBResponse.h"
#include "rec/util/cd/DedupeCDDB.h"
#include "rec/util/cd/Socket.h"
#include "rec/util/cd/StripLines.h"
#include "rec/util/file/VirtualFile.h"

using namespace rec::music;

namespace rec {
namespace util {
namespace cd {

namespace {

void splitTitle(Metadata *album) {
  // Split title up.
  StringPair title = splitLine(album->album_title(), '/');
  if (!title.second.empty()) {
    album->set_artist(title.first);
    album->set_album_title(title.second);
  }
}

void splitTitle(Album *album) { splitTitle(album->mutable_album()); }

void splitTracks(Album* album) {
  // Look for likely song splits.
  static const char splits[] = "/:-";
  bool splitting;
  for (uint i = 0; !splitting && i < arraysize(splits); ++i) {
    char ch = splits[i];
    splitting = true;
    for (int j = 0; splitting && j < album->track_size(); ++j)
      splitting = (album->track(i).track_title().find(ch) > 0);

    for (int j = 0; splitting && j < album->track_size(); ++j) {
      StringPair p = splitLine(album->track(j).track_title(), ch);
      album->mutable_track(j)->set_artist(p.first);
      album->mutable_track(j)->set_track_title(p.second);
    }
  }
}

void addAlbumValue(const String& key, const string& v, Album* a) {
  Metadata* data = a->mutable_album();
  if (key == "DISCID")
    data->set_discid(v);

  else if (key == "DYEAR")
    data->set_year(v);

  else if (key == "DGENRE")
    data->set_genre(v);

  else if (key == "DTITLE")
    *data->mutable_album_title() += v;

  else if (key.startsWith("TTITLE"))
    *a->mutable_track(key.getTrailingIntValue())->mutable_track_title() += v;

  else if (!(key.startsWith("EXT") || key == "PLAYORDER"))
    LOG(ERROR) << "Unknown key " << key << " '" << v << "'";
}

void fillAlbum(const StringArray& cds, int tracks, Album* album) {
  while (album->track_size() < tracks)
    album->add_track();

  for (int i = 1; i < cds.size() - 1; ++i) {
    const String& line = cds[i];
    if (line.length() && line[0] != '#') {
      int loc = line.indexOfChar('=');
      if (loc == -1) {
        LOG(ERROR) << "Couldn't find = in line " << line;
      } else {
        String value = line.substring(loc + 1);
        if (value.length() || !value.startsWith("EXT"))
          addAlbumValue(line.substring(0, loc), str(value), album);
      }
    }
  }
}

void fillAlbumList(Socket* sock, const TrackOffsets& off, AlbumList* albums) {
  const String offsets = trackOffsetString(off);
  StringArray cds = getPossibleCDs(sock, offsets);
  for (int i = 1; i < cds.size() - 1; ++i) {
    Album album;
    fillAlbum(getCDData(sock, cds[i]), off.size() - 1, &album);
    splitTitle(&album);
    splitTracks(&album);
    addIfNotSimilar(albums, album);
  }
}

}  // namespace

#define DEFAULT_USER        "anonymous"
#define DEFAULT_HOST        "localhost"
#define DEFAULT_TIMEOUT     10

#ifdef USE_FREEDB

#define DEFAULT_SERVER      "ecddb.gracenote.com"
#define DEFAULT_PORT        8080

#else

#define DEFAULT_SERVER      "freedb.org"
#define DEFAULT_PORT        888

#endif

String fillAlbums(const TrackOffsets& off, AlbumList* albums) {
  try {
    Socket sock;
    connect(&sock, DEFAULT_SERVER, DEFAULT_PORT, DEFAULT_TIMEOUT * 1000);
    readCDDBResponse(&sock);
    makeCDDBRequest("cddb hello anonymous localhost slowgold 1.0", &sock);
    makeCDDBRequest("proto 6", &sock);

    fillAlbumList(&sock, off, albums);
    return "";
  } catch (Exception& e) {
    return e.what();
  }
}

// TODO:  this should use the persistence layer!!
Album getCachedAlbum(const VirtualFile& file, const TrackOffsets& off) {
  Album album;
  File shadow = getShadowFile(file, "album");
  if (!copy::copy(shadow, &album)) {
    AlbumList albums;
    String error = fillAlbums(off, &albums);
    if (error.length()) {
      LOG(ERROR) << "CDDB gave us an error: " << error;
    } else if (!albums.album_size()) {
      LOG(ERROR) << "CDDB gave us no information";
    } else {
      album = albums.album(0);
      if (!copy::copy(album, &shadow))
        LOG(ERROR) << "Couldn't save CDDB information";
    }
  }

  return album;
}

}  // namespace cd
}  // namespace util
}  // namespace rec
