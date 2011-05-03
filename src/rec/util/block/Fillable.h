#ifndef __REC_UTIL_BLOCK_FILLABLE__
#define __REC_UTIL_BLOCK_FILLABLE__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

class Fillable {
 public:
  Fillable(int64 len = 0) : length_(len), position_(0) {}
  virtual ~Fillable() {}

  static const int WAIT_TIME = 0;
  static const int MAX_WAIT_TIME = 7000;

  void setPosition(int64 position);
  void setLength(int64 length);

  void fillNextBlock();
  bool isFull() const;
  bool hasFilled(const Block& b) const;

 protected:
  virtual Size doFillNextBlock(const Block& b) = 0;

  // Called when the buffer is actually full.
  virtual void onFilled() {}

  CriticalSection lock_;
  BlockSet filled_;
  int64 length_;

 private:
  int64 position_;

  DISALLOW_COPY_AND_ASSIGN(Fillable);
};

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_FILLABLE__
