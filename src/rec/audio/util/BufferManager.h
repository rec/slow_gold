#ifndef __REC_AUDIO_BUFFERMANAGER__
#define __REC_AUDIO_BUFFERMANAGER__

#include "rec/base/base.h"

/*
  Components:
    the buffer: a C-style array of frames with a length
    a map from blocks of frames in the source to blocks within the block of memory

 */


namespace rec {
namespace audio {

template <typename Frame>
  vector<Frame> frames_;

class TimeMap {
 public:
  TimeMap() : enabled_(false) {}

  void add(SampleTime from, SampleTime to, SampleTime length) {
    from_[-from] = Range(to, to + length);
    to_[-to] = Range(from, from + length);
  }

 private:
  typedef Range<SampleTime> TimeRange;
  typedef std::map<SampleTime, TimeRange> RangeMap;

  static SampleTime get(const RangeMap& map, SampleTime time) {
    Map::const_iterator i = map_->lower_bound(-time);

  }

  RangeMap from_;
  RangeMap to_;
  bool enabled_;
};


class BufferManager {
 public:
  BufferManager();

  ptr<Source> source_;
  LoopPointList loopPoints_;

  SampleTime time_;
  SampleTime requestedTime_;
  ptr<Callback> requestedTimeCallback_;

  TimeMap timeMap_;
  Thumbnail thumbnail_;

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BufferManager);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_BUFFERMANAGER__
