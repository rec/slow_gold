#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>

#include "rec/data/UntypedEditable.h"
#include "rec/util/DefaultRegistry.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace data {

template <typename Proto>
class TypedEditable : public UntypedEditable,
                      public Broadcaster<const Proto&> {
 public:
  TypedEditable(const File& file, const VirtualFile& vf);
  virtual ~TypedEditable() {}

  // Get a consistent snapshot of the current value.
  const Proto get() const;
  virtual const string getTypeName() const { return proto_.GetTypeName(); }
  virtual void onDataChange();

  // Add a new listener and update them later in the update thread.
  //void addToUpdateQueue(Listener<const Proto&>* listener);

  // virtual bool update();

 private:
  // typedef std::vector< typename Listener<const Proto&>* > UpdateQueue;
  // UpdateQueue updateQueue_;
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TypedEditable);
};

//
// Implementations.
//
extern const DefaultRegistry& defaultRegistry();

template <typename Proto>
TypedEditable<Proto>::TypedEditable(const File& file, const VirtualFile& vf)
    : UntypedEditable(file, vf, &proto_) {
  if (!readFromFile())
    proto_ = defaultRegistry().getDefault<Proto>(vf);
}

// Get a consistent snapshot of the current value.
template <typename Proto>
const Proto TypedEditable<Proto>::get() const {
  Lock l(UntypedEditable::lock_);
  return proto_;
}

template <typename Proto>
void TypedEditable<Proto>::onDataChange() {
  Proto p = get();
  messageBroadcaster_.broadcast(p);
  broadcast(p);
}

#if 0
template <typename Proto>
void TypedEditable<Proto>::addListenerAndUpdate(Listener<const Proto&>* listener) {
  addListener(listener);

  Lock l(UntypedEditable::lock_);
  updateQueue_.push_back(listener);
}

template <typename Proto>
bool TypedEditable<Proto>::update() {
  UpdateQueue toUpdate;
  {
    Lock l(UntypedEditable::lock_);
    toUpdate.swap(updateQueue_);
  }
  if (!UntypedEditable::update()) {
    Proto p = get();
    for (int i = 0; i < toUpdate.size(); ++i)
      (*toUpdate[i])(p);
  }
}

#endif

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
