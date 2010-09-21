#ifndef __REC_PERSIST_UNDOQUEUE__
#define __REC_PERSIST_UNDOQUEUE__

#include <vector>

#include "rec/base/base.h"
#include "rec/base/Cast.h"
#include "rec/persist/Writeable.h"
#include "rec/persist/Copy.h"
#include "rec/persist/DataRegistry.h"
#include "rec/proto/Proto.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

// An undoable message with state.
class UndoQueue {
 public:
  typedef google::protobuf::Message Message;

  UndoQueue(Message* m) : message_(m) {}
  ~UndoQueue() {
    apply();
  }

  void push(proto::Operation* op) {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }

  bool apply() {
    ScopedLock l(lock_);
    if (queue_.empty())
      return false;

    for (OperationList::iterator i = queue_.begin(); i != queue_.end(); ++i) {
      undos_.push_back(applyOperation(**i, message_.get()));
      delete *i;
    }
    queue_.clear();
    return true;
  }

  template <typename Proto>
  Proto value() const {
    ScopedLock l(lock_);

    DCHECK_EQ(Proto::default_instance().getTypeName(), message_->getTypeName());
    Proto p;
    p.CopyFrom(*message_);
    return p;
  }

 private:
  typedef std::vector<proto::Operation*> OperationList;

  OperationList queue_;
  OperationList undos_;

  scoped_ptr<Message> message_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UndoQueue);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_UNDOQUEUE__
