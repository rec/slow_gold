#pragma once

#include "rec/base/base.h"

/*
  Components:
    the buffer: a C-style array of frames with a length
    a map from blocks of frames in the source to blocks within the block of memory

 */


namespace rec {
namespace audio {

template <typename Frame> vector<Frame> frames_;

class TimeMap {
 public:
  TimeMap() : enabled_(false) {}

  void add(SampleTime from, SampleTime to, SampleTime length) {
    from_[from] = Range(to, to + length);
    to_[to] = Range(from, from + length);
  }

 private:
  typedef Range<SampleTime> TimeRange;
  class Compare {
    bool operator()(const TimeRange& x, const TimeRange& y) { return x > y; }
  };

  typedef std::map<SampleTime, TimeRange, Compare> RangeMap;

  static SampleTime get(const RangeMap& map, SampleTime time) {
    // Get the first element with a start time not less than the given time.
    Map::const_iterator i = map_->lower_bound(time);
    if (i != map_->end()) {
      SampleTime diff = time - i->first;
      DCHECK_GE(diff, 0);
      SampleTime length = i->second.size();
      if (diff < length)
        return i->second.begin_ + diff;
    }
    return -1;
  }

  RangeMap from_;
  RangeMap to_;
  bool enabled_;
};

// Services I need:
// requestTime
// fillOnce
// fillBuffer
class BufferManager {
 public:
  BufferManager();

  void requestTime(SampleTime time) {
    Lock l(requestLock_);
    requestedTime_ = time;
  }

  void fillOnce() {
  }

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
  }

 private:
  std::unique_ptr<Source> source_;
  LoopPointList loopPoints_;

  SampleTime time_;
  SampleTime requestedTime_;
  std::unique_ptr<Callback> requestedTimeCallback_;

  TimeMap timeMap_;
  Thumbnail thumbnail_;

  CriticalSection lock_;
  CriticalSection requestLock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BufferManager);
};

}  // namespace audio
}  // namespace rec
