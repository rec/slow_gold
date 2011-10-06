#ifndef __REC_MUSIC_CREATEMUSICFILEREADER__
#define __REC_MUSIC_CREATEMUSICFILEREADER__

#include "rec/base/base.h"

namespace rec {
namespace music {

AudioFormatReader* createMusicFileReader(const VirtualFile& file);

}  // namespace music
}  // namespace rec

#endif  // __REC_MUSIC_CREATEMUSICFILEREADER__
