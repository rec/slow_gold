#ifndef __REC_SLOW_ISWHOLESONG__
#define __REC_SLOW_ISWHOLESONG__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class IsWholeSong {
 public:
  enum WholeSong { ONE_SEGMENT, WHOLE_SONG, SONG_IS_ONE_SEGMENT };
  virtual WholeSong isWholeSong() const = 0;
  virtual ~IsWholeSong() {}
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_ISWHOLESONG__
