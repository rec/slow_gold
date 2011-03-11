#ifndef __REC_UTIL_BLOCK_FILLER__
#define __REC_UTIL_BLOCK_FILLER__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

class Filler {
 public:
  Filler(int len, int b) : length_(len), blockSize_(b), position_(0) {}
  virtual ~Filler() {}

  static const int WAIT_TIME = 0;
  static const int MAX_WAIT_TIME = 7000;

  void setPosition(int position);
  bool hasFilled(const Block& b) const;

  void fillNextBlock();
  bool isFull() const;
  int getLength() const { return length_; }

  bool waitUntilFilled(const Block& block, int maxWaitTime = MAX_WAIT_TIME,
                       int waitTime = WAIT_TIME);

 protected:
  virtual void doFillNextBlock(const Block& b) = 0;

  // Called when the buffer is actually full.
  virtual void onFilled() {}
  CriticalSection lock_;

  const int length_;
  const int blockSize_;

  BlockSet filled_;

 private:
  int position_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Filler);
};

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_FILLER__
