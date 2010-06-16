#ifndef __REC_BUFFER_MULTI_CLIENT_BUFFER
#define __REC_BUFFER_MULTI_CLIENT_BUFFER

#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "rec/base/scoped_ptr.h"
#include "rec/util/locker.h"
#include "rec/block/Block.h"
#include "rec/buffer/client-manager.h"
#include "rec/buffer/producer-queue.h"

#include "rec/util/locker.h"

using std::map;
using std::set;
using std::pair;

using rec::util::LockInterface;
using rec::util::Locker;

namespace rec {
namespace buffer {

template <typename Buffer>
class Multi<Buffer> {
 public:
  Multi(Buffer* buffer, LockInterface* lock);
  ~Multi();

  typedef std::pair<Multi*, ClientId> Client;

  Client newClient();
  void freeClient(const Client& client);

 private:
  ProducerQueue producerQueue_;
  ClientManager clientManager_;

  scoped_ptr<LockInterface> lock_;
  scoped_ptr<Buffer> buffer;

  friend template <typename In, typename Out> class InOut;
  DISALLOW_COPY_AND_ASSIGN(Multi);
};

// Copy from a MultiClientBuffer::Client.
template <typename In, typename Out>
Size copy(Size size, Multi<In>::Client* in, Out* out);

// Copy to a MultiClientBuffer.
template <typename BufferIn, typename BufferOut>
Size copy(Size size, In *in, Multi<Out>* out);

}  // namespace buffer
}  // namespace rec

#endif  // __REC_BUFFER_MULTI_CLIENT_BUFFER
