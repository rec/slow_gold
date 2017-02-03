#pragma once

#include "rec/base/base.h"

namespace rec {

namespace music {
class Album;
class AlbumList;
class Metadata;
}

namespace util {
namespace cd {

string normalize(const string& s);

bool similar(const string& x, const string& y);
bool similarTrack(const music::Metadata& x, const music::Metadata& y);
bool similar(const music::Album& x, const music::Album& y);

void addIfNotSimilar(music::AlbumList* albums, const music::Album& album);

}  // namespace cd
}  // namespace util
}  // namespace rec

