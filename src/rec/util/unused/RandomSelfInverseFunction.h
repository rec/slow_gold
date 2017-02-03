#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

struct ByteFunction {
  static const int COUNT = 256;
  byte function[COUNT];
  byte operator()(byte b) const { return function[b]; }

 private:
  JUCE_LEAK_DETECTOR(ByteFunction);
};

ByteFunction randomSelfInverseFunction(unsigned seed);

}  // namespace util
}  // namespace rec

