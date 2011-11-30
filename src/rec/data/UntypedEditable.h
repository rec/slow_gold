#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/data/Editable.h"
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

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
