#include <gtest/gtest.h>
#include "rec/audio/FillQueue.h"

namespace rec {
namespace audio {
namespace buffer {

TEST(RecAudio, FillQueue) {
  FillQueue queue(5);

  EXPECT_EQ(queue.Advance(FILLING), -1);   // 0, 5, 5, 5
  EXPECT_EQ(queue.Advance(FULL), -1);
  EXPECT_EQ(queue.Advance(EMPTYING), -1);
  EXPECT_EQ(queue.Advance(EMPTY), 4);      // 0, 4, 5, 5
  EXPECT_EQ(queue.Advance(EMPTY), 3);      // 0, 3, 5, 5
  EXPECT_EQ(queue.Advance(FILLING), 4);    // 0, 3, 4, 5
  EXPECT_EQ(queue.Advance(FULL), 4);       // 0, 3, 4, 4
  EXPECT_EQ(queue.Advance(EMPTYING), 4);   // 4, 3, 4, 4
  EXPECT_EQ(queue.Advance(EMPTY), 2);      // 4, 2, 4, 4
  EXPECT_EQ(queue.Advance(EMPTY), 1);      // 4, 1, 4, 4
  EXPECT_EQ(queue.Advance(EMPTY), 0);      // 4, 0, 4, 4
  EXPECT_EQ(queue.Advance(EMPTY), 4);      // 4, 4, 4, 4

  EXPECT_EQ(queue.Advance(FILLING), 3);
  EXPECT_EQ(queue.Advance(FILLING), 2);
}

TEST(RecAudio, DoubleQueue) {
  //                                         E  Fi F  Ei
  FillQueue queue(2);                     // 0, 2, 2, 2   E, E
  EXPECT_EQ(queue.Advance(EMPTY), 1);     // 0, 1, 2, 2   E, Fi
  EXPECT_EQ(queue.Advance(FILLING), 1);   // 0, 1, 1, 2   E, Fa

  EXPECT_EQ(queue.Advance(EMPTY), 0);     // 0, 0, 1, 2   Fi, Fa
  EXPECT_EQ(queue.Advance(FILLING), 0);   // 0, 0, 0, 2   Fb, Fa

  EXPECT_EQ(queue.Advance(FULL), 1);      // 0, 0, 0, 1   Fb, Ei
  EXPECT_EQ(queue.Advance(EMPTYING), 1);  // 1, 0, 0, 1   Fb, E
  EXPECT_EQ(queue.Advance(EMPTY), 1);     // 1, 1, 0, 1   Fb, Fi
  EXPECT_EQ(queue.Advance(FILLING), 1);   // 1, 1, 1, 1   Fb, Fc
  EXPECT_EQ(queue.Advance(FULL), 0);     // 1, 1, 1, 1
  EXPECT_EQ(queue.Advance(FULL), 1);     // 1, 1, 1, 1
}


}  // namespace buffer
}  // namespace audio
}  // namespace rec
