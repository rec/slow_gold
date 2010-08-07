#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include "rec/base/base.h"
#include "rec/persist/Copy.h"
#include "rec/persist/App.h"

#include "google/protobuf/message.h"

#include "juce_amalgamated.h"

namespace rec {
namespace persist {


template <typename Proto> class Accessor;

template <typename Proto>
class Data : public Writeable {
 public:
  Data(const String& name, App* app)
      : app_(app),
        file_(app->getDataFile(name)) {
    app_->addData(this);
    copy(file_, (google::protobuf::Message*) &proto_);
  }

  virtual ~Data() {
    write();
    app_->removeData(this);
  }

  virtual void doWrite() {
    copy((const google::protobuf::Message&) proto_, &file_);
  }

  friend class Accessor<Proto>;

 private:
  App* app_;
  File file_;
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
