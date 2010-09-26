#ifndef __REC_PERSIST_UNTYPEDDATA__
#define __REC_PERSIST_UNTYPEDDATA__

#include "rec/base/base.h"
#include "rec/base/basictypes.h"
#include "rec/base/scoped_ptr.h"
#include "rec/proto/Setter.h"
#include "rec/proto/Types.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

typedef proto::arg::Setter Setter;
class AppBase;
class App;

class UntypedData : public Setter::Listener {
 public:
  typedef google::protobuf::Message Message;
  virtual ~UntypedData();

  // Change the data with an Operation.  op will eventually be deleted.  The
  // change is performed on a different thread so it is likely that the value of
  // get() won't immediately be updated.
  virtual void change(proto::Operation* op);

  Setter* setter() { return &setter_; }
  
 protected:
  friend class App;

  UntypedData(const File& file, Message* message, AppBase* app);
  void readFromFile() const;

  void update();
  void writeToFile() const;

  virtual void changeCallback() = 0;

  typedef std::vector<proto::Operation*> OperationList;

  OperationList queue_;
  OperationList undo_;

  File file_;
  mutable Message* message_;
  Setter setter_;

  AppBase* app_;
  CriticalSection lock_;
  mutable bool alreadyReadFromFile_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UntypedData);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_UNTYPEDDATA__
