#include "rec/buffer/multi-client-buffer.h"

using std::make_pair;

namespace rec {
namespace buffer {


template <typename Buffer>
Multi<Buffer>::Multi(Buffer* buffer, LockInterface *lock)
    : buffer_(buffer), lock_(lock) {
}

template <typename Buffer>
Multi<Buffer>::Client Multi<Buffer>::newClient() {
  return make_pair(this, clientManager_.newClient());
}

template <typename Buffer>
void Multi<Buffer>::freeClient(const Client& client) {
  clientManager_.freeClient(client.second);
}

namespace {

template <typename In, typename Out>
class InOut {
 public:
  InOut(In in, Out out) : in_(in), out_(out) {}

  Size copyAll(Size size) {
    BlockList blocks;

    {
      Locker l(getLock(inOut));
      allocateBlocks(size, &blocks);
    }

    Size copied = 0;
    for (BlockList::iterator i = blocks.begin(); i != blocks.end(); ++i) {
      copied += copyBlock(*i);
      {
        Locker l(getLock());
        freeBlock(*i);
      }
    }
    return copied;
  }

  typedef InOut<In, Multi<Out>* > Producer;
  typedef InOut<Multi<In>::Client*, Out> Client;

 private:
  In in_;
  Out out_;

  void allocateBlocks(Size size, BlockList* blocks);
  Size copyBlock(const Block& block);
  LockInterface* getLock();
  void freeBlock(const Block& block);
};

template <typename In, typename Out>
void InOut<In, Out>::Producer::allocateBlocks(Size size, BlockList* blocks) {
  out_->producerQueue->allocate(size, blocks);
}

template <typename In, typename Out>
Size InOut<In, Out>::Producer::copyBlock(const Block& block) {
  return copy(getSize(block), in_, make_pair(out_->getBuffer(), block.begin()));
}

template <typename In, typename Out>
LockInterface* InOut<In, Out>::Producer::getLock() {
  return out_->lock_.get();
}

template <typename In, typename Out>
void InOut<In, Out>::Producer::freeBlock(const Block& block) {
  out_->clientManager_.addBlocks(producerQueue_.produce(block));
}


template <typename In, typename Out>
void InOut<In, Out>::Client::allocateBlocks(Size size, BlockList* blocks) {
  Multi<In> *m = in_->first;
  m->clientManager->getBlocks(in_->second, size(), blocks);
}

template <typename In, typename Out>
Size InOut<In, Out>::Client::copyBlock(const Block& block) {
  Multi<In> *m = in_->first;
  return copy(getSize(block), make_pair(m->getBuffer(), block.begin()), out_);
}

template <typename In, typename Out>
LockInterface* InOut<In, Out>::Client::getLock() {
  Multi<In> *m = in_->first;
  return m->lock_.get();
}

template <typename In, typename Out>
void InOut<In, Out>::Client::freeBlock(const Block& block) {
  Multi<In> *m = in_->first;
  m->producerQueue._remove(m->clientManager_.erase(in_->second, block.first));
}

}  // namespace

template <typename In, typename Out>
Size copy(Size size, Multi<In>::Client* in, Out* out) {
  return InOut(in, out).copy(size);
}

template <typename BufferIn, typename BufferOut>
Size copy(Size size, In *in, Multi<Out>* out) {
  return InOut(in, out).copy(size);
}

#endif

}  // namespace buffer
}  // namespace rec
