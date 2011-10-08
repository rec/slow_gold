#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>

#include "rec/data/persist/UntypedEditable.h"
#include "rec/data/proto/GetProtoName.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace persist {

class App;

template <typename Proto>
class Data : public data::UntypedEditable,
             public Broadcaster<const Proto&>,
             public Listener<const Proto&> {
 public:
  // Get a consistent snapshot of the current value.
  const Proto get() const {
    ScopedLock l(UntypedEditable::lock_);
    return proto_;
  }

  virtual void operator()(const Proto&) {
    DCHECK(false);
  }

  virtual string getTypeName() const { return proto_.GetTypeName(); }

  virtual ~Data() {}

 protected:
  virtual void onDataChange() {
    Proto p;
    {
      ScopedLock l(UntypedEditable::lock_);
      p.CopyFrom(proto_);
    }
    messageBroadcaster()->broadcast(p);
    broadcast(p);
  }

 private:
  Proto proto_;

  Data(const File& file, App* app) : UntypedEditable(file, &proto_, app) {}

  friend class App;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};


}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
