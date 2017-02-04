#pragma once

#include "rec/base/SampleTime.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace util {

using SampleRange = Range<SampleTime>;
using SampleRangeSet = SampleRange::Set;
using SampleRangeVector = SampleRange::Vector;

}  // namespace util
}  // namespace rec
