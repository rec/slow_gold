#ifndef __REC_MUSIC_METADATA__
#define __REC_MUSIC_METADATA__

#include "rec/base/base.h"
#include "rec/music/Metadata.pb.h"

namespace rec {
namespace music {

music::Metadata getTrack(const music::Album& album, int i);
music::Metadata getMetadata(const StringPairArray& metadata);

}  // namespace music
}  // namespace rec

#endif  // __REC_MUSIC_METADATA__
