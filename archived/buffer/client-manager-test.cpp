#include <gtest/gtest.h>

#include "rec/buffer/client-manager.h"

namespace rec {
namespace buffer {

typedef ClientManager::Client Client;

TEST(ClientManager, NewClient) {
  ClientManager m;
  Client c1 = m.newClient();
  Client c2 = m.newClient();
  EXPECT_EQ(c1, 0);
  EXPECT_EQ(c2, 1);
  m.freeClient(c1);

  Client c3 = m.newClient();
  Client c4 = m.newClient();

  EXPECT_EQ(c3, 1);
  EXPECT_EQ(c4, 2);
  m.freeClient(c3);

  Client c5 = m.newClient();
  Client c6 = m.newClient();

  EXPECT_EQ(c5, 3);
  EXPECT_EQ(c6, 4);
  m.freeClient(c4);
  m.freeClient(c5);
  m.freeClient(c6);
  EXPECT_EQ(m.newClient(), 1);
}

TEST(ClientManager, AddAndGetBlocks) {
  ClientManager m;
  BlockList blocks;
  blocks.push_back(Block(0, 100));
  blocks.push_back(Block(100, 200));
  blocks.push_back(Block(200, 300));
  blocks.push_back(Block(300, 400));

  m.addBlocks(blocks);
  EXPECT_EQ(m.empty(), false);

  BlockList result;
  EXPECT_EQ(m.getBlocks(0, 100, &result), 0u);
  EXPECT_EQ(result.size(), 0u);
  EXPECT_EQ(m.empty(), false);
  m.clean();
  EXPECT_EQ(m.empty(), true);

  Client c1 = m.newClient();
  Client c2 = m.newClient();
  m.addBlocks(blocks);

  EXPECT_EQ(m.getBlocks(c1, 75, &result), 75u);
  EXPECT_EQ(result.size(), 1u);
  EXPECT_EQ(result[0].first, 0u);
  EXPECT_EQ(result[0].second, 75u);

  result.clear();
  EXPECT_EQ(m.getBlocks(c1, 150, &result), 150u);
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0].first, 75u);
  EXPECT_EQ(result[0].second, 100u);
  EXPECT_EQ(result[1].first, 100u);
  EXPECT_EQ(result[1].second, 200u);
  EXPECT_EQ(result[2].first, 200u);
  EXPECT_EQ(result[2].second, 225u);

  result.clear();
  EXPECT_EQ(m.getBlocks(c2, 400, &result), 400u);
  EXPECT_EQ(result.size(), 4u);

  m.freeClient(c1);
  m.erase(c2, 0);
  m.erase(c2, 100);
  m.erase(c2, 200);
  EXPECT_EQ(m.empty(), false);
  m.erase(c2, 300);
  EXPECT_EQ(m.empty(), true);
}

}  // namespace buffer
}  // namespace rec


