#include <gtest/gtest.h>

#include "rec/util/unused/Circular.h"

namespace rec {
namespace util {

namespace {

TEST(Circular, Constructor) {
    EXPECT_TRUE(Circular<int>(8) == Circular<int>(0, 0, 8));
}

TEST(Circular, Fillable1) {
    EXPECT_TRUE(Circular<int>(8).fillableBlock() == Range<int>(0, 8));
}

TEST(Circular, Fillable2) {
    EXPECT_TRUE(Circular<int>(0, 4, 8).fillableBlock() == Range<int>(4, 8));
}

TEST(Circular, Fillable3) {
    EXPECT_TRUE(Circular<int>(4, 12, 8).fillableBlock() == Range<int>(4, 4));
}

TEST(Circular, Fill) {
    Circular<int> c(8);
    EXPECT_EQ(c.size(), 0);

    c.fill(3);
    EXPECT_EQ(c.size(), 3);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(3, 8));

    c.fill(3);
    EXPECT_EQ(c.size(), 6);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(6, 8));

    c.fill(3);
    EXPECT_EQ(c.size(), 8);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(0, 0));

    c.fill(3);
    EXPECT_EQ(c.size(), 8);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(0, 0));

    c.consume(2);
    EXPECT_EQ(c.size(), 6);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(0, 2));

    c.consume(3);
    EXPECT_EQ(c.size(), 3);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(0, 5));

    c.fill(2);
    EXPECT_EQ(c.size(), 5);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(2, 5));

    c.consume(2);
    EXPECT_EQ(c.size(), 3);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(2, 7));

    c.consume(2);
    EXPECT_EQ(c.size(), 1);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(2, 8));

    c.fill(2);
    EXPECT_EQ(c.size(), 3);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(4, 8));

    c.consume(2);
    EXPECT_EQ(c.size(), 1);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(4, 8));

    c.fill(2);
    EXPECT_EQ(c.size(), 3);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(6, 8));

    c.consume(2);
    EXPECT_EQ(c.size(), 1);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(6, 8));

    c.fill(2);
    EXPECT_EQ(c.size(), 3);
    EXPECT_TRUE(c.fillableBlock() == Range<int>(0, 5));
}

}  // namespace
}  // namespace util
}  // namespace rec
