#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/data/Data.h"
#include "rec/util/listener/Listener.h"

namespace rec {

namespace persist { class App; }
namespace persist { class AppInstance; }

namespace data {

class UntypedData : public data::Data {
 public:
  virtual ~UntypedData();

  // Change the data with an OperationList.  op will eventually be deleted.  The
  // change is performed on a different thread so it is likely that the value of
  // get() won't immediately be updated.
  virtual void operator()(OperationList* op);

  // Request an update to this data in a different thread.
  void requestUpdate();
  bool fileReadSuccess() const { return fileReadSuccess_; }

  virtual const Value getValue(const Address& address) const;
  virtual bool hasValue(const Address& address) const;
  virtual int getSize(const Address& address) const;
  virtual void copyTo(Message* message) const;

  Broadcaster<const Message&>* messageBroadcaster() {
    return &messageBroadcaster_;
  }

  template <typename T> bool fill(T* t) const {
    if (t->GetTypeName() != getTypeName()) {
      LOG(ERROR) << "Couldn't fill " << t->GetTypeName()
                 << " from " << getTypeName();
      return false;
    }

    ScopedLock l(lock_);
    copyTo(t);
    return true;
  }

  Message* clone() const;

 protected:
  virtual void onDataChange() = 0;
  virtual string getTypeName() const = 0;

  // Update the clients in this thread.
  void update();

  UntypedData(const File& file, Message* message, persist::App* app);
  void readFromFile() const;

  void writeToFile() const;

  typedef std::vector<data::OperationList*> OperationQueue;

  OperationQueue queue_;
  OperationQueue undo_;

  ptr<File> file_;
  mutable Message* message_;

  persist::App* app_;
  CriticalSection lock_;

  friend class persist::AppInstance;

 private:
  mutable bool alreadyReadFromFile_;
  mutable bool fileReadSuccess_;
  Broadcaster<const Message&> messageBroadcaster_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UntypedData);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
