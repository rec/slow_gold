#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/data/Editable.h"
#include "rec/util/listener/Listener.h"

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

  Broadcaster<const Message&>* messageBroadcaster() {
    return &messageBroadcaster_;
  }

  template <typename Proto> bool fill(Proto* t) const;

  Message* clone() const;

 protected:
  virtual void onDataChange() = 0;

  // Update the clients in this thread.
  void update();

  UntypedEditable(const File& file, Message* message, persist::EditableFactory*);
  void readFromFile() const;
  void writeToFile() const;

  typedef std::vector<data::OperationList*> OperationQueue;

  OperationQueue queue_;

  ptr<File> file_;
  mutable Message* message_;

  persist::EditableFactory* editableFactory_;
  CriticalSection lock_;

  friend class persist::EditableUpdateQueue;
  friend class persist::EditableFactory;

 private:
  mutable bool alreadyReadFromFile_;
  mutable bool fileReadSuccess_;
  Broadcaster<const Message&> messageBroadcaster_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UntypedEditable);
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
