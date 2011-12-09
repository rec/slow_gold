#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/data/Editable.h"
#include "rec/data/proto/MessageField.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class UntypedEditable : public Editable {
 public:
  virtual ~UntypedEditable();

  // Request an update to this data in a different thread.
  virtual bool fileReadSuccess() const { return fileReadSuccess_; }

  virtual const Value getValue(const Address& address) const;
  virtual bool hasValue(const Address& address) const;
  virtual int getSize(const Address& address) const;
  virtual void copyTo(Message* message) const;
  MessageField createMessageField(const Address&) const;

  template <typename Proto> bool fill(Proto* t) const;

  virtual Message* clone() const;
  const VirtualFile& virtualFile() const { return virtualFile_; }

  virtual void applyOperations(const Operations& olist,
                               Operations* undoes = NULL);
  virtual void applyLater(Operations* op);

  virtual bool readFromFile() const;
  virtual bool writeToFile() const;

  // Update listeners in this thread.
  // Return true if any clients were update.
  virtual bool update();
  virtual void needsUpdate();
  virtual void onDataChange() = 0;
  virtual bool isEmpty() const { return false; }

  Broadcaster<const Message&>* broadcaster() { return &broadcaster_; }

 protected:
  UntypedEditable(const File& file, const VirtualFile& vf, Message* message);

  CriticalSection lock_;

  OperationList queue_;
  const File file_;
  const VirtualFile virtualFile_;

  mutable Message* message_;

 private:
  mutable bool alreadyReadFromFile_;
  mutable bool fileReadSuccess_;

  Broadcaster<const Message&> broadcaster_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedEditable);
};

template <typename Proto>
bool UntypedEditable::fill(Proto* t) const {
  if (t->GetTypeName() != getTypeName()) {
    LOG(DFATAL) << "Couldn't fill " << t->GetTypeName()
               << " from " << getTypeName();
    return false;
  }

  Lock l(lock_);
  copyTo(t);
  return true;
}

#if 0
class EmptyEditable : public UntypedEditable {
 public:
  EmptyEditable(const string& name) : UntypedEditable(File(), VirtualFile(), NULL),
                                      typeName_(name) {}
  virtual ~EmptyEditable() {}
  virtual void onDataChange() {}

  virtual Message* clone() const { return NULL; }
  virtual bool hasValue(const Address&) const { return false; }
  virtual const Value getValue(const Address&) const { return Value(); }
  virtual const VirtualFile& virtualFile() const {
    return VirtualFile::default_instance();
  }
  virtual const string getTypeName() const { return typeName_; }
  virtual int getSize(const Address&) const { return 0; }
  virtual void copyTo(Message*) const {}
  virtual void needsUpdate()  {}

  virtual bool fileReadSuccess() const { return false; }
  virtual bool readFromFile() const { return false; }
  virtual bool writeToFile() const { return true; }
  virtual void applyLater(Operations*) {}
  virtual void applyOperations(const Operations&, Operations*) {}

  virtual bool isEmpty() const { return true; }

 private:
  const string typeName_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(EmptyEditable);
};

#endif

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
