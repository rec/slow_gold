#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>

#include "rec/data/persist/UntypedEditable.h"
#include "rec/data/proto/GetProtoName.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace data {

template <typename Proto>
class TypedEditable : public data::UntypedEditable,
                      public Broadcaster<const Proto&> {
 public:
  TypedEditable(const File& file, const VirtualFile& vf,
                const Proto& dflt = Proto::default_instance())
      : UntypedEditable(file, vf, &proto_) {
    if (!readFromFile())
      proto_ = dflt;
  }

  // Get a consistent snapshot of the current value.
  const Proto get() const {
    ScopedLock l(UntypedEditable::lock_);
    return proto_;
  }

  virtual const string getTypeName() const { return proto_.GetTypeName(); }
  virtual ~TypedEditable() {}

 protected:
  virtual void onDataChange() {
    Proto p = get();
    messageBroadcaster_.broadcast(p);
    broadcast(p);
  }

 private:
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TypedEditable);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
