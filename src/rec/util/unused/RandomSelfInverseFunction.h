#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

struct ByteFunction {
    static const int COUNT = 256;
    uint8 function[COUNT];
    uint8 operator()(uint8 b) const { return function[b]; }

  private:
    JUCE_LEAK_DETECTOR(ByteFunction);
};

ByteFunction randomSelfInverseFunction(unsigned seed);

}  // namespace util
}  // namespace rec
