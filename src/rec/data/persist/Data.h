#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>
#include <glog/logging.h>

#include "rec/base/base.h"
#include "rec/data/persist/UntypedData.h"
#include "rec/util/Listener.h"

namespace rec {
namespace persist {

class App;

template <typename Proto>
class Data : public UntypedData,
             public util::Listener<const Proto&>::Set {
 public:
  // Get a snapshot of the current data.
  Proto get() const {
    ScopedLock l(lock_);
    
    Proto p;
    p.CopyFrom(proto_);
    return p;
  }
    
  // Add a listener so you get notified every time the data changes.
  virtual void operator()(proto::Operation* op) { UntypedData::operator()(op); }

  virtual ~Data() {}

 protected:
  virtual void changeCallback() { tellListeners(get()); }

 private:
  friend class App;

  Data(const File& file, App* app) : UntypedData(file, &proto_, app) {}

  Proto proto_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};


}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
