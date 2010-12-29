#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/base/base.h"
#include "rec/data/proto/Setter.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace persist {

class App;
class AppInstance;

typedef proto::arg::Setter Setter;

class UntypedData : public Setter {
 public:
  virtual ~UntypedData();

  // Change the data with an Operation.  op will eventually be deleted.  The
  // change is performed on a different thread so it is likely that the value of
  // get() won't immediately be updated.
  virtual void operator()(proto::Operation* op);

  void update() {
    (*this)((proto::Operation*)NULL);
  }

  bool fileReadSuccess() const { return fileReadSuccess_; }

 protected:
  friend class AppInstance;

  UntypedData(const File& file, Message* message, App* app);
  void readFromFile() const;

  void doUpdate();
  void writeToFile() const;

  virtual void changeCallback() = 0;

  typedef std::vector<proto::Operation*> OperationList;

  OperationList queue_;
  OperationList undo_;

  ptr<File> file_;
  mutable Message* message_;

  App* app_;
  CriticalSection lock_;

 private:
  mutable bool alreadyReadFromFile_;
  mutable bool fileReadSuccess_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(UntypedData);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
