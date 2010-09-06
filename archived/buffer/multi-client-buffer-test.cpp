#include <gtest/gtest.h>

#include "rec/buffer/multi-client-buffer.h"

using std::pair;
using std::make_pair;
using rec::util::LockInterface;

namespace rec {
namespace buffer {

struct FakeBuffer {
  typedef pair<Size, Block> Action;

  vector<Action> fromList_;
  vector<Action> toList_;

  Size copyFrom(Size begin, const Block& b, FakeBuffer*) {
    fromList_.push_back(make_pair(begin, b));
    return b.size();
  }
  Size copyTo(Size begin, const Block& b, FakeBuffer*) {
    toList_.push_back(make_pair(begin, b));
    return b.size();
  }
};

Size copy(Size size, FakeBuffer* in, pair<FakeBuffer*, Size> out) {
};

class FakeLock : public LockInterface {
  virtual void enter() {}
  virtual void exit() {}
};

TEST(Buffer, MultiClientBuffer) {
  Multi<FakeBuffer> mcb(new FakeBuffer(), new FakeLock());
  FakeBuffer in, out;

  Client client1 = mcb.newClient();
  Client client2 = mcb.newClient();
  mcb.copyFrom(Block(0, 100), &in);
  mcb.copyFrom(Block(0, 100), &in);
}

}  // namespace buffer
}  // namespace rec
