#ifndef __REC_BUFFER_PRODUCER_QUEUE
#define __REC_BUFFER_PRODUCER_QUEUE

#include "rec/buffer/blocks.h"

namespace rec {
namespace buffer {

class ProducerQueue {
 public:
  ProducerQueue() {}

  /** allocate() pushes a list of allocated of blocks totalling size. */
  void allocate(Size size,  BlockList* blocks);

  /** produce() marks a block as actually having been produced.*/
  BlockList produce(const Block& block);

  /** getProduct() pushes a list of blocks that are freshly produced
   *  and aren't waiting on blocks ahead of them onto "product" and then
   *  removes them from the production queue. */

  /** Mark a block as available for reuse after it's been consumed. */
  void remove(const BlockList& blocks);

 private:
  BlockSet all_;
  BlockList production_;
  BlockSet produced_;

  DISALLOW_COPY_AND_ASSIGN(ProducerQueue);
};

}  // namespace buffer
}  // namespace rec

#endif  // __REC_BUFFER_PRODUCER_QUEUE
