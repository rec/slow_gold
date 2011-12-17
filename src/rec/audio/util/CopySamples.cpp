#include "rec/audio/util/CopySamples.h"

namespace rec {
namespace audio {

namespace {

int channels(const BufferTime& bt) { return bt.buffer_->getNumChannels(); }
Samples<44100> size(const BufferTime& bt) { return bt.buffer_->getNumSamples(); }
Samples<44100> remaining(const BufferTime& b) { return size(b) - b.time_; }

struct Copier {
  Copier(const BufferTime& from, const BufferTime& to, Samples<44100> count)
      : from_(from), to_(to), count_(count) {
  }

  Samples<44100> copy() const {
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
    // TODO: bug Jules
    to_.buffer_->copyFrom(f, to_.time_.toInt(), *from_.buffer_, t,
                          from_.time_.toInt(), count_.toInt());
  }

  void mix(int chanFrom, int chanTo) const {
    Samples<44100> startFrom = from_.time_;
    Samples<44100> startTo = to_.time_;
    for (int c = 0; c < chanTo; ++c) {
      // This probably isn't right.
      int c1 = (chanFrom * c) / chanTo;
      int c2 = (chanFrom * (c + 1) - 1) / chanTo;
      float* fromSamp = from_.buffer_->getSampleData(c1, startFrom.toInt());

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
  const Samples<44100> count_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Copier);
};

Samples<44100> restrictCount(const BufferTime& bt, Samples<44100> count) {
  Samples<44100> remains = remaining(bt);
  if (count <= remains)
    return count;

  return remains;
}

}  // namespace

Samples<44100> copy(const BufferTime& from, const BufferTime& to, Samples<44100> cnt) {
  return Copier(from, to, restrictCount(from, restrictCount(to, cnt))).copy();
}

#if 0
namespace {

Samples<44100> copy(bool copyFirstToSecond,
                const BufferTime& x, const BufferTime& y, Samples<44100> c) {
  return copyFirstToSecond ? copy(x, y, c) : copy(y, x, c);
}

BufferTime add(const BufferTime& bt, Samples<44100> d) {
  return BufferTime(bt.buffer_, bt.time_ + d);
}

BufferTime reset(const BufferTime& bt, Samples<44100> t = 0.0) {
  return BufferTime(bt.buffer_, t);
}

}  // namespace

Samples<44100> copyCircular(const BufferTime& circ, Samples<44100> size,
                        const BufferTime& reg, Samples<44100> count,
                        bool toReg) {
  Samples<44100> available = (size - circ.time_);
  Samples<44100> n = std::min(available, count);
  Samples<44100> copied = copy(toReg, circ, reg, n);
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

Samples<44100> copyFromCircular(const BufferTime& from, Samples<44100> fromSize,
                            const BufferTime& to, Samples<44100> count) {
  return copyCircular(from, fromSize, to, count, true);
}

Samples<44100> copyToCircular(const BufferTime& from, const BufferTime& to,
                          Samples<44100> toSize, Samples<44100> count) {
  return copyCircular(to, toSize, from, count, false);
}

void clear(const BufferTime& bt, Samples<44100> count) {
  if (count > 0)
    bt.buffer_->clear(bt.time_, count);
}

#endif

}  // namespace audio
}  // namespace rec
