#ifndef __REC_UTIL_BLOCK_FILLABLE__
#define __REC_UTIL_BLOCK_FILLABLE__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

class Fillable {
 public:
  Fillable(int len, int b) : length_(len), blockSize_(b), position_(0) {}
  virtual ~Fillable() {}

  static const int WAIT_TIME = 0;
  static const int MAX_WAIT_TIME = 7000;

  void setPosition(int position);

  void fillNextBlock();
  bool isFull() const;
  bool hasFilled(const Block& b) const;

  const int length_;
  const int blockSize_;

 protected:
  virtual Size doFillNextBlock(const Block& b) = 0;

  // Called when the buffer is actually full.
  virtual void onFilled() {}

  CriticalSection lock_;
  BlockSet filled_;

 private:
  int position_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Fillable);
};

#if 0
bool waitUntilFilled(const Fillable&, const Block& block,
                     int maxWaitTime = Fillable::MAX_WAIT_TIME,
                     int waitTime = Fillable::WAIT_TIME);
#endif

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_FILLABLE__
