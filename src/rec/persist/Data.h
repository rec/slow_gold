#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <string>

#include "rec/base/base.h"
#include "rec/base/Cast.h"
#include "rec/persist/Writeable.h"
#include "rec/persist/Copy.h"
#include "rec/persist/DataRegistry.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

template <typename Proto> class Access;

template <typename Proto>
class Data : public Writeable {
 public:
  typedef google::protobuf::Message Message;

  File dataFileName(const File& file) {
    return File(file.getFullPathName() + "." + copy(typeName_));
  }

  Data(const File& file) : typeName_(typeName(Proto::default_instance())),
                           message_(getData(typeName_)),
                           file_(dataFileName(file)) {
    CHECK(message_) << "Didn't understand " << typeName_;
    if (!copy(file_, &proto_)) {
      LOG(ERROR) << "New file " << file.getFullPathName().toCString();
      proto_.CopyFrom(*message_);
    }
  }

  virtual void doWrite() {
    copy(proto_, &file_);
  }

  const Proto get() const {
    ScopedLock l(lock_);
    return proto_;
  }

  friend class Access<Proto>;

  class Access {
   public:
    Access(Data<Proto>* data) : data_(data), locker_(data->lock_) {}

    const Proto& operator*()  const { return data_->proto_; }
    const Proto* operator->() const { return &data_->proto_; }

    Proto& operator*() {
      data_->changed_ = true;
      return data_->proto_;
    }

    Proto* operator->() {
      data_->changed_ = true;
      return &data_->proto_;
    }

   private:
    Data<Proto>* data_;
    ScopedLock locker_;

    DISALLOW_COPY_ASSIGN_AND_EMPTY(Access);
  };

 private:
  string typeName_;
  const Message* message_;
  File file_;
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
