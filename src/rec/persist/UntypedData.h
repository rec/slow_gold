#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/base/base.h"
#include "rec/proto/Types.h"
#include "rec/proto/Setter.h"

namespace rec {
namespace persist {

class App;
class AppInstance;
  
typedef proto::arg::Setter Setter;

class UntypedData : public Setter::Listener {
 public:
  virtual ~UntypedData();

  // Change the data with an Operation.  op will eventually be deleted.  The
  // change is performed on a different thread so it is likely that the value of
  // get() won't immediately be updated.
  virtual void change(proto::Operation* op);

  Setter* setter() { return &setter_; }

 protected:
  friend class AppInstance;

  UntypedData(const File& file, Message* message, App* app);
  void readFromFile() const;

  void update();
  void writeToFile() const;

  virtual void changeCallback() = 0;

  typedef std::vector<proto::Operation*> OperationList;

  OperationList queue_;
  OperationList undo_;

  scoped_ptr<File> file_;
  mutable Message* message_;
  Setter setter_;

  App* app_;
  scoped_ptr<CriticalSection> lock_;
  mutable bool alreadyReadFromFile_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UntypedData);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
