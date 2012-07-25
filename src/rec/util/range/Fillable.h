#ifndef __REC_UTIL_RANGE_FILLABLE__
#define __REC_UTIL_RANGE_FILLABLE__

#include "rec/util/LoopPoint.h"

namespace rec {
namespace util {

class Fillable {
 public:
  Fillable(SampleTime len = 0) : length_(len), position_(0) {}
  virtual ~Fillable() {}

  static const int WAIT_TIME = 0;
  static const int MAX_WAIT_TIME = 7000;

  void setNextFillPosition(SampleTime position);
  SampleTime position() const;
  void setLength(SampleTime length);
  SampleTime length() const;

  SampleTime fillNextBlock();
  bool isFull() const;
  bool hasFilled(const SampleRange& b) const;
  SampleRangeVector filled() const { Lock l(lock_); return filled_; }
  virtual void reset();
  double filledPercent() const;

 protected:
  virtual SampleTime doFillNextBlock(const SampleRange& b) = 0;

  // Called when the buffer is actually full.
  virtual void onFilled() {}

  CriticalSection lock_;
  SampleRangeVector filled_;
  SampleTime length_;

 private:
  SampleTime position_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Fillable);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE_FILLABLE__
