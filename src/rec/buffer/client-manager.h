#ifndef __REC_BUFFER_CLIENT_MANAGER
#define __REC_BUFFER_CLIENT_MANAGER

#include <map>
#include <vector>

#include "rec/base/disallow.h"
#include "rec/base/scoped_ptr.h"
#include "rec/buffer/blocks.h"

namespace rec {
namespace buffer {

typedef int ClientId;

class ClientManager {
 public:
  ClientManager() {}

  typedef std::map<ClientId, Size> Offsets;
  typedef std::vector<Offsets> OffsetsList;

  /** Return a new client. */
  ClientId newClient();

  /** Free a client and potentially all the blocks connected to it. */
  void freeClient(ClientId client);

  /** Add a new list of free blocks that can be given to clients. */
  void addBlocks(const BlockList& blocks);

  /** Get a list of blocks for a given client, and advance the counters. */
  Size getBlocks(ClientId client, Size size, BlockList* blocks);

  /** Mark a block completely done for a client.  Returns the blocks that are
   *  completely done for all clients. */
  BlockList erase(ClientId client, Size begin);

  /** Remove all blocks that are not referenced by any clients. */
  BlockList clean();

  bool empty() const { return queue_.empty(); }

 private:
  Offsets clients_;

  // These next two arrays are parallel!
  OffsetsList offsetsList_;
  BlockList queue_;

  friend class ClientManagerTester;

  DISALLOW_COPY_AND_ASSIGN(ClientManager);
};

}  // namespace buffer
}  // namespace rec

#endif  // __REC_BUFFER_CLIENT_MANAGER
