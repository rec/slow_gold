#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/RandomSelfInverseFunction.h"

namespace rec {
namespace util {
namespace {

bool testEqual(const ByteFunction& x, const ByteFunction& y) {
  for (int i = 0; i < ByteFunction::COUNT; ++i)
    if (x(i) != y(i))
      return false;
  return true;
}

void testInvertible(const ByteFunction& fn) {
  for (int i = 0; i < ByteFunction::COUNT; ++i)
    EXPECT_EQ(i, fn(fn(i)));
}

void testInvertible(int seed) {
  testInvertible(randomSelfInverseFunction(seed));
}

int invariants(const ByteFunction& fn) {
  int t = 0;
  for (int i = 0; i < ByteFunction::COUNT; ++i)
    if (i == fn(i))
      ++t;
  return t;
}

int invariants(int seed) {
  return invariants(randomSelfInverseFunction(seed));
}


TEST(RandomSelfInverseFunction, All) {
  ByteFunction f12 = randomSelfInverseFunction(12);
  ByteFunction f0 = randomSelfInverseFunction(0);

  EXPECT_TRUE(testEqual(f12, randomSelfInverseFunction(12)));
  EXPECT_FALSE(testEqual(f0, f12));

  testInvertible(f12);
  testInvertible(f0);

  EXPECT_EQ(invariants(0), 2);
  EXPECT_EQ(invariants(1), 8);
  EXPECT_EQ(invariants(12), 2);
  EXPECT_EQ(invariants(173042), 16);  // !!
  
	for (int i = 0; i < 100; ++i) 
    EXPECT_LE(invariants(i), 11) << "failed on " << i;

	for (int i = 0; i < 100; ++i) 
    testInvertible(i);

#ifdef TIME_TO_BURN  
	for (int i = 0; i < 10000; ++i) 
    EXPECT_LE(invariants(i), 12) << "failed on " << i;

  
	for (int i = 0; i < 100000; ++i) 
    EXPECT_LE(invariants(i), 13) << "failed on " << i;

	for (int i = 0; i < 1000000; ++i) {
    if (i == 173042)
      EXPECT_EQ(invariants(i), 16);
    else
      EXPECT_LE(invariants(i), 14) << "failed on " << i;
  }
#endif
}

}  // namespace
}  // namespace util
}  // namespace rec
