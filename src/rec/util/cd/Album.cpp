#include <glog/logging.h>

#include "rec/util/cd/Album.h"
#include "rec/util/cd/Album.pb.h"
#include "rec/util/cd/CDDBResponse.h"
#include "rec/util/cd/DedupeCDDB.h"
#include "rec/util/cd/Socket.h"
#include "rec/util/Exception.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace util {
namespace cd {

namespace {

typedef std::pair<string, string> StringPair;

StringPair split(const string& s, int ch) {
  string first = s, second;
  int loc = s.find(ch);
  if (loc != -1) {
    first = String(s.substr(0, loc - 1).c_str()).trimEnd().toCString();
    second = String(s.substr(0, loc - 1).c_str()).trimStart().toCString();
  }
  return std::make_pair(first, second);
}

}  // namespace

void splitTitle(Album *album) {
  // Split title up.
  StringPair title = split(album->title(), '/');
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
      StringPair p = split(album->track(j).title(), ch);
      album->mutable_track(j)->set_artist(p.first);
      album->mutable_track(j)->set_title(p.second);
    }
  }
}

void fillAlbum(const StringPairArray& cd, Album* album) {
  const StringArray& keys = cd.getAllKeys();
  for (int i = 0; i < keys.size(); ++i) {
    const String& key = keys[i];
    const string& value = cd[key].toCString();
    if (key == "DISCID")
      album->set_discid(value);

    else if (key == "DYEAR")
      album->set_year(value);

    else if (key == "DGENRE")
      album->set_genre(value);

    else if (key == "DTITLE")
      album->set_title(value);

    else if (key.startsWith("TTITLE"))
      album->add_track()->set_title(value);

    else if (!(key.startsWith("EXT") || key == "PLAYORDER"))
      LOG(ERROR) << "Unknown key " << key.toCString() << " '" << value << "'";
  }
}

StringPairArray parseCDData(const StringArray& cds) {
  StringPairArray result;
  for (int i = 1; i < cds.size(); ++i) {
    const String& line = cds[i];
    if (line.length() && line[0] != '#') {
      int loc = line.indexOfChar('=');
      if (loc == -1)
        throw Exception(string("Couldn't find = in line ") + line.toCString());

      String value = line.substring(loc + 1);
      if (value.length() || !value.startsWith("EXT"))
        result.set(line.substring(0, loc), value);
    }
  }

  return result;
}

void fillAlbumList(Socket* sock, const TrackOffsets& off, AlbumList* albums) {
  const String offsets = trackOffsetString(off);
  StringArray cds = getPossibleCDs(sock, offsets);
  for (int i = 0; i < cds.size(); ++i) {
    Album album;
    fillAlbum(parseCDData(getCDData(sock, cds[i])), &album);
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
    makeCDDBRequest("cddb hello anon localhost slowgold 1.0", &sock);
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
