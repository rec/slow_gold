#ifndef __REC_AUDIO_FILLQUEUE
#define __REC_AUDIO_FILLQUEUE

#include <strings.h>

#include "rec/base/basictypes.h"

namespace rec {
namespace audio {
namespace buffer {

enum FillState { EMPTY, FILLING, FULL, EMPTYING };

class FillQueue {
 public:
  FillQueue(int size) : size_(size) { Clear(); }

  void Clear() {
    // Inline this when we finish cleaning
    memset(ranges_, 0, sizeof(ranges_));
    ranges_[EMPTY].second = size_;
  }

  int Advance(FillState state) {
    QueueRange& range = ranges_[state];
    if (!length(range))
      return -1;

    QueueRange& nextRange = ranges_[(state == EMPTYING) ? EMPTY : state + 1];
    ++length(nextRange);
    if (begin(nextRange))
      --begin(nextRange);
    else
      begin(nextRange) = size_ - 1;

    --length(range);
    return (begin(range) + length(range)) % size_;
  }

  void Output() {
    // Get rid of this when we're done debugging.
    for (int i = EMPTY; i <= EMPTYING; ++i)
      std::cerr << begin(ranges_[i]) << "-" << begin(ranges_[i]) << ", ";
    std::cerr << std::endl;
  }

 private:
  typedef std::pair<int, int> QueueRange;
  inline static int& length(QueueRange& range) { return range.second; }
  inline static int& begin(QueueRange& range) { return range.first; }

  QueueRange ranges_[EMPTYING + 1];
  int size_;

  DISALLOW_COPY_AND_ASSIGN(FillQueue);
};

}  // namespace buffer
}  // namespace audio
}  // namespace rec


#endif __REC_AUDIO_FILLQUEUE
