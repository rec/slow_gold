#ifndef __REC_AUDIO_FORMAT_MPG123_CLEANGENRE__
#define __REC_AUDIO_FORMAT_MPG123_CLEANGENRE__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

string cleanGenre(int);
string cleanGenre(const string&);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_MPG123_CLEANGENRE__
