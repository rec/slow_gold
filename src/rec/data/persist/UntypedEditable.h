#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/data/Editable.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {

namespace persist { class EditableFactory; }
namespace persist { class EditableUpdateQueue; }

namespace data {

class UntypedEditable : public Editable {
 public:
  virtual ~UntypedEditable();

  // Change the data with an OperationList.  op will eventually be deleted.  The
  // change is performed on a different thread so it is likely that the value of
  // get() won't immediately be updated.
  virtual void apply(OperationList* op);

  // Request an update to this data in a different thread.
  bool fileReadSuccess() const { return fileReadSuccess_; }

  virtual const Value getValue(const Address& address) const;
  virtual bool hasValue(const Address& address) const;
  virtual int getSize(const Address& address) const;
  virtual void copyTo(Message* message) const;

  virtual string getTypeName() const = 0;

  typedef Listener<const Message&> Listener;

  Broadcaster<const Message&>* messageBroadcaster() {
    return &messageBroadcaster_;
  }
  template <typename Proto> bool fill(Proto* t) const;

  Message* clone() const;
  const VirtualFile& virtualFile() const { return virtualFile_; }

 protected:
  virtual void onDataChange() = 0;

  // Update the clients in this thread.
  void update();

  UntypedEditable(const File& file, const VirtualFile& vf, Message* message);

  void readFromFile() const;
  void writeToFile() const;

  CriticalSection lock_;

  OperationQueue queue_;
  Broadcaster<const Message&> messageBroadcaster_;
  const File file_;
  const VirtualFile virtualFile_;

  mutable Message* message_;

 private:
  mutable bool alreadyReadFromFile_;
  mutable bool fileReadSuccess_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UntypedEditable);

  friend class persist::EditableFactory;
  friend class persist::EditableUpdateQueue;
};

template <typename Proto>
bool UntypedEditable::fill(Proto* t) const {
  if (t->GetTypeName() != getTypeName()) {
    LOG(ERROR) << "Couldn't fill " << t->GetTypeName()
               << " from " << getTypeName();
    return false;
  }

  ScopedLock l(lock_);
  copyTo(t);
  return true;
}

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
