#include <gtest/gtest.h>

#include "rec/buffer/producer-queue.h"

namespace rec {
namespace buffer {

TEST(Buffer, ProducerQueue) {
  ProducerQueue producerQueue;
  {
    BlockList blocks;
    producerQueue.allocate(100, &blocks);
    EXPECT_EQ(blocks.size(), 1u);
    EXPECT_EQ(blocks[0].begin_, 0u);
    EXPECT_EQ(blocks[0].end_, 100u);
  }

  {
    BlockList blocks;
    producerQueue.allocate(100, &blocks);
    EXPECT_EQ(blocks.size(), 1u);
    EXPECT_EQ(blocks[0].begin_, 100u);
    EXPECT_EQ(blocks[0].end_, 200u);
  }

  {
    BlockList blocks = producerQueue.produce(Block(100u, 200u));
    EXPECT_EQ(blocks.size(), 0u);
  }

  {
    BlockList blocks = producerQueue.produce(Block(0u, 100u));
    EXPECT_EQ(blocks.size(), 2u);

    EXPECT_EQ(blocks[0].begin_, 0u);
    EXPECT_EQ(blocks[0].end_, 100u);
    EXPECT_EQ(blocks[1].begin_, 100u);
    EXPECT_EQ(blocks[1].end_, 200u);
  }
}

}  // namespace buffer
}  // namespace rec
