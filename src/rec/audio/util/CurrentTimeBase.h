#pragma once

#include "rec/util/range/SampleRange.h"

namespace rec {
namespace audio {
namespace util {

class CurrentTimeBase {
  public:
    CurrentTimeBase() {}
    virtual ~CurrentTimeBase() {}
    virtual void jumpToTime(SampleTime) = 0;
    virtual SampleTime requestedTime() const = 0;
    virtual const SampleRangeVector timeSelection() const = 0;
    virtual SampleTime time() const = 0;
};

}  // namespace util
}  // namespace audio
}  // namespace rec
