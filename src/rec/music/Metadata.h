#ifndef __REC_MUSIC_METADATA__
#define __REC_MUSIC_METADATA__

#include "rec/base/base.h"
#include "rec/music/Metadata.pb.h"

namespace rec {
namespace music {

Metadata getTrack(const music::Album& album, int i);
Metadata getMetadata(const StringPairArray& metadata);

string getTitle(const File&);
string getTitle(const Metadata&);
string getTitle(const VirtualFile&);

template <typename T1, typename T2>
string getTitle(const T1& t1, const T2& t2) {
  string r = getTitle(t1);
  if (r.empty())
    r = getTitle(t2);
  return r;
}

template <typename T1, typename T2, typename T3>
string getTitle(const T1& t1, const T2& t2, const T3& t3) {
  string r = getTitle(t1);
  if (r.empty())
    r = getTitle(t2, t3);
  return r;
}

}  // namespace music
}  // namespace rec

#endif  // __REC_MUSIC_METADATA__
