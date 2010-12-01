#include <glog/logging.h>

#include "rec/util/cd/Album.h"
#include "rec/util/cd/Album.pb.h"
#include "rec/util/cd/CDDBResponse.h"
#include "rec/util/cd/DedupeCDDB.h"
#include "rec/util/cd/Socket.h"
#include "rec/util/cd/StripLines.h"
#include "rec/util/Exception.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace util {
namespace cd {

void splitTitle(Album *album) {
  // Split title up.
  StringPair title = splitLine(album->title(), '/');
  if (!title.second.empty()) {
    album->set_artist(title.first);
    album->set_title(title.second);
  }
}

void splitTracks(Album* album) {
  // Now look for likely song splits.
  static const char splits[] = "/:-";
  bool splitting;
  for (int i = 0; !splitting && i < arraysize(splits); ++i) {
    char ch = splits[i];
    splitting = true;
    for (int j = 0; splitting && j < album->track_size(); ++j)
      splitting = (album->track(i).title().find(ch) > 0);

    for (int j = 0; splitting && j < album->track_size(); ++j) {
      StringPair p = splitLine(album->track(j).title(), ch);
      album->mutable_track(j)->set_artist(p.first);
      album->mutable_track(j)->set_title(p.second);
    }
  }
}

void fillAlbum(const StringArray& cds, int tracks, Album* album) {
  while (album->track_size() < tracks)
    album->add_track();
  
  for (int i = 1; i < cds.size() - 1; ++i) {
    const String& line = cds[i];
    if (line.length() && line[0] != '#') {
      int loc = line.indexOfChar('=');
      if (loc == -1) {
        LOG(ERROR) << "Couldn't find = in line " << line.toCString();
      } else {
        String value = line.substring(loc + 1);
        if (value.length() || !value.startsWith("EXT"))
          addAlbumValue(line.substring(0, loc), value.toCString(), album);
      }
    }
  }
}

void addAlbumValue(const String& key, const string& value, Album* album) {
  if (key == "DISCID")
    album->set_discid(value);

  else if (key == "DYEAR")
    album->set_year(value);

  else if (key == "DGENRE")
    album->set_genre(value);

  else if (key == "DTITLE")
    *album->mutable_title() += value;

  else if (key.startsWith("TTITLE")) {
    LOG(INFO) << "Title! " << key << " " << value;
    (*album->mutable_track(key.getTrailingIntValue())->mutable_title()) += value;
  }

  else if (!(key.startsWith("EXT") || key == "PLAYORDER"))
    LOG(ERROR) << "Unknown key " << key.toCString() << " '" << value << "'";
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

#define DEFAULT_USER        "anonymous"
#define DEFAULT_HOST        "localhost"
#define DEFAULT_SERVER      "freedb.org"
#define DEFAULT_PORT        888
#define DEFAULT_TIMEOUT     10
#define DEFAULT_PATH_QUERY  "/~cddb/cddb.cgi"
#define DEFAULT_PATH_SUBMIT "/~cddb/submit.cgi"

String fillAlbums(const TrackOffsets& off, AlbumList* albums) {
  try {
    Socket sock;
    connect(&sock, DEFAULT_SERVER, DEFAULT_PORT, DEFAULT_TIMEOUT * 1000);
    // makeCDDBRequest("", &sock);
    readCDDBResponse(&sock);
    makeCDDBRequest("cddb hello anonymous localhost slowgold 1.0", &sock);
    makeCDDBRequest("proto 6", &sock);
    fillAlbumList(&sock, off, albums);
    return "";
  } catch (Exception& e) {
    return e.what();
  }
}

}  // namespace cd
}  // namespace util
}  // namespace rec
