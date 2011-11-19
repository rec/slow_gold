#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>

#include "rec/data/UntypedEditable.h"
#include "rec/util/DefaultRegistry.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/Listener.h"

namespace rec {
namespace data {

template <typename Proto>
class TypedEditable : public UntypedEditable, public Broadcaster<const Proto&> {
 public:
  TypedEditable(const File& file, const VirtualFile& vf);
  virtual ~TypedEditable() {}

  // Get a consistent snapshot of the current value.
  const Proto get() const;
  virtual const string getTypeName() const { return proto_.GetTypeName(); }
  virtual void onDataChange();

  typedef Listener<const Proto&> ProtoListener;

  // Add a new listener and update them later in the update thread.
  void addListenerAndUpdate(ProtoListener* listener);
  virtual bool update();

 private:
  typedef std::vector<ProtoListener* > UpdateQueue;
  UpdateQueue updateQueue_;
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TypedEditable);
};

template <typename Proto>
class EmptyTypedEditable : public TypedEditable<Proto> {
 public:
  EmptyTypedEditable()
      : TypedEditable<Proto>(File(), VirtualFile::default_instance()) {
  }
  virtual ~EmptyTypedEditable() {}
  virtual bool readFromFile() const { return false; }
  virtual bool writeToFile() const { return true; }
  virtual bool fileReadSuccess() const { return false; }
  virtual void applyLater(Operations*) {}
  virtual void applyOperations(const Operations&, Operations*) {}
  virtual bool isEmpty() const { return true; }

 private:
  DISALLOW_COPY_AND_ASSIGN(EmptyTypedEditable);
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
  broadcast(get());
}

template <typename Proto>
void TypedEditable<Proto>::addListenerAndUpdate(ProtoListener* listener) {
  addListener(listener);

  Lock l(UntypedEditable::lock_);
  updateQueue_.push_back(listener);
  needsUpdate();
}

template <typename Proto>
bool TypedEditable<Proto>::update() {
  UpdateQueue toUpdate;
  {
    Lock l(UntypedEditable::lock_);
    toUpdate.swap(updateQueue_);
  }
  if (UntypedEditable::update())
    return true;

  if (toUpdate.empty())
    return false;

  Proto p = get();
  for (int i = 0; i < toUpdate.size(); ++i)
    (*toUpdate[i])(p);

  return true;
}

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
