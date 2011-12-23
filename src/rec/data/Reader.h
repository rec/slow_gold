#ifndef __REC_DATA_READER__
#define __REC_DATA_READER__

#include <google/protobuf/message.h>

#include "rec/data/Data.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
struct Reader {
  Reader(Data* d) : data_(d) { initialize(); }
  Reader(const VirtualFile* vf) : data_(getData<Proto>(vf)) { initialize(); }

  ~Reader() {}

  const Proto& operator*() const { return get(); }
  const Proto* operator->() const { return &get(); }
  const Proto& get() const {
    return *proto_;
  }

  Message* cloneMessage() const {
    return proto_ ? clone(*proto_) : NULL;
  }

 protected:
  Data* const data_;
  ptr<Lock> locker_;
  Proto* proto_;

 private:
  void initialize() {
    locker_.reset(new Lock(data_->lock_));
    proto_ = dynamic_cast<Proto*>(data_->message_.get());
  }
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_READER__
