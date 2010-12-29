#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>
#include "rec/base/base.h"
#include "rec/data/persist/UntypedData.h"
#include "rec/util/listener/Listener.h"
#include "rec/data/proto/GetProtoName.h"

namespace rec {
namespace persist {

class App;

template <typename Proto>
class Data : public UntypedData, public Broadcaster<const Proto&> {
 public:
  // Get a consistent snapshot of the current value.
  Proto get() const {
    ScopedLock l(lock_);
    return proto_;
  }

  virtual ~Data() {
    DLOG(INFO) << "Deleting data: " << data::proto::getName(Proto::default_instance());
  }

 protected:
  virtual void changeCallback() { broadcast(get()); }

 private:
  friend class App;

  Data(const File& file, App* app) : UntypedData(file, &proto_, app) {}

  Proto proto_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
