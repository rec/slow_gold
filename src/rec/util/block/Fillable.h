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

  void setNextFillPosition(int64 position);
  int64 position() const;
  void setLength(int64 length);
  int64 length() const;

  int64 fillNextBlock();
  bool isFull() const;
  bool hasFilled(const Block& b) const;
  BlockSet filled() const { Lock l(lock_); return filled_; }
  void clear() { filled_.clear(); }
  double filledPercent() const;

 protected:
  virtual Size doFillNextBlock(const Block& b) = 0;

  // Called when the buffer is actually full.
  virtual void onFilled() {}

  CriticalSection lock_;
  BlockSet filled_;
  int64 length_;

 private:
  int64 position_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Fillable);
};

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_FILLABLE__
