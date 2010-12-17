#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>
#include <glog/logging.h>

#include "rec/base/base.h"
#include "rec/data/persist/UntypedData.h"
#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace persist {

class App;

template <typename Proto>
class Data : public UntypedData, public listener::Broadcaster<const Proto&> {
 public:
  // Get a snapshot of the current.
  Proto get() const {
    ScopedLock l(lock_);
    return proto_;
  }

  virtual ~Data() {}

 protected:
  virtual void changeCallback() {
    Proto proto = get();
    listener::Broadcaster<const Proto&>::broadcast(proto);
    listener::Broadcaster<const Message&>::broadcast(proto);
  }

 private:
  friend class App;

  Data(const File& file, App* app) : UntypedData(file, &proto_, app) {}

  Proto proto_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
