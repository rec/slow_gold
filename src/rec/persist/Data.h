#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <string>

#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"

#include "rec/base/base.h"
#include "rec/base/Cast.h"
#include "rec/persist/Writeable.h"
#include "rec/persist/Copy.h"


#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

template <typename Proto> class Access;

template <typename Proto>
class Data : public Writeable {
 public:
  typedef google::protobuf::Message Message;

  Data(const File& file, const char* initial = "") : file_(file) {
    if (!(copy(file_, &proto_) || copy(std::string(initial), &proto_))) {
      LOG_FIRST_N(ERROR, 10) << "Couldn't read file "
                             << file.getFullPathName().toCString()
                             << " or initial " << initial;
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
  File file_;
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
