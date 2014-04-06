#include "rec/audio/util/CopySamples.h"

namespace rec {
namespace audio {

namespace {

int channels(const BufferTime& bt) { return bt.buffer_->getNumChannels(); }
SampleTime size(const BufferTime& bt) { return bt.buffer_->getNumSamples(); }
SampleTime remaining(const BufferTime& b) { return size(b) - b.time_; }

struct Copier {
  Copier(const BufferTime& from, const BufferTime& to, SampleTime count)
      : from_(from), to_(to), count_(count) {
  }

  SampleTime copy() const {
    for (int ch = 0; ch < channels(to_); ++ch)
      copy(ch);
    return count_;
  }

 private:
  void copy(int ch) const {
    if (channels(to_) == channels(from_))
      copy(ch, ch);

    else if (channels(from_) == 1)
      copy(0, ch);

    else
      mix(ch, channels(from_));
  }

  void copy(int f, int t) const {
    to_.buffer_->copyFrom(f, to_.time_.toInt(), *from_.buffer_, t,
                          from_.time_.toInt(), count_.toInt());
  }

  void mix(int chanFrom, int chanTo) const {
    SampleTime startFrom = from_.time_;
    SampleTime startTo = to_.time_;
    for (int c = 0; c < chanTo; ++c) {
      // This probably isn't right.
      int c1 = (chanFrom * c) / chanTo;
      int c2 = (chanFrom * (c + 1) - 1) / chanTo;
      float* fromSamp = from_.buffer_->getWritePointer(c1, startFrom.toInt());

      if (c1 == c2) {
        to_.buffer_->copyFrom(c, startTo.toInt(), fromSamp, count_.toInt());
      } else {
        to_.buffer_->copyFrom(c, startTo.toInt(), fromSamp, count_.toInt(), 0.5f);
        to_.buffer_->addFrom(c, startTo.toInt(), *from_.buffer_, c2,
                             startFrom.toInt(), count_.toInt(), 0.5f);
      }
    }
  }

  const BufferTime from_;
  const BufferTime to_;
  const SampleTime count_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Copier);
};

SampleTime restrictCount(const BufferTime& bt, SampleTime count) {
  SampleTime remains = remaining(bt);
  if (count <= remains)
    return count;

  return remains;
}

}  // namespace

SampleTime copy(const BufferTime& from, const BufferTime& to, SampleTime cnt) {
  return Copier(from, to, restrictCount(from, restrictCount(to, cnt))).copy();
}

#if 0
namespace {

SampleTime copy(bool copyFirstToSecond,
                const BufferTime& x, const BufferTime& y, SampleTime c) {
  return copyFirstToSecond ? copy(x, y, c) : copy(y, x, c);
}

BufferTime add(const BufferTime& bt, SampleTime d) {
  return BufferTime(bt.buffer_, bt.time_ + d);
}

BufferTime reset(const BufferTime& bt, SampleTime t = 0.0) {
  return BufferTime(bt.buffer_, t);
}

}  // namespace

SampleTime copyCircular(const BufferTime& circ, SampleTime size,
                        const BufferTime& reg, SampleTime count,
                        bool toReg) {
  SampleTime available = (size - circ.time_);
  SampleTime n = std::min(available, count);
  SampleTime copied = copy(toReg, circ, reg, n);
  if (n < count)
    copied += copy(toReg, reset(circ), add(reg, n), count - n);

  if (copied < count) {
    if (toReg || ) {
      clear(reg.add(copied), count - copied);
    } else {
    }
  }
  return copied;
}

SampleTime copyFromCircular(const BufferTime& from, SampleTime fromSize,
                            const BufferTime& to, SampleTime count) {
  return copyCircular(from, fromSize, to, count, true);
}

SampleTime copyToCircular(const BufferTime& from, const BufferTime& to,
                          SampleTime toSize, SampleTime count) {
  return copyCircular(to, toSize, from, count, false);
}

void clear(const BufferTime& bt, SampleTime count) {
  if (count > 0)
    bt.buffer_->clear(bt.time_, count);
}

#endif

}  // namespace audio
}  // namespace rec
