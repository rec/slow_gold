#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include "rec/base/base.h"
#include "rec/base/Cast.h"
#include "rec/persist/Writeable.h"
#include "rec/persist/Copy.h"

#include "google/protobuf/message.h"

#include "juce_amalgamated.h"

namespace rec {
namespace persist {

template <typename Proto> class Access;

template <typename Proto>
class Data : public Writeable {
 public:
  Data(const File& file) : file_(file) {
    copy(file_, implicit_cast<google::protobuf::Message*>(&proto_));
  }

  virtual void doWrite() {
    copy(implicit_cast<const google::protobuf::Message&>(proto_), &file_);
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
  File file_;
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
