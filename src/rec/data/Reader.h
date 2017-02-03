#pragma once

#include <google/protobuf/message.h>

#include "rec/data/Data.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
class Reader {
 public:
  Reader(Data* d) : data_(d) { initialize(); }
  Reader(const VirtualFile& vf = global()) : data_(getData<Proto>(vf)) {
    initialize();
  }

  ~Reader() {}

  const Proto& operator*() const { return get(); }
  const Proto* operator->() const { return &get(); }
  const Proto& get() const {
    return *proto_;
  }

  Message* cloneMessage() const {
    return proto_ ? clone(*proto_) : nullptr;
  }

 protected:
  Data* const data_;
  std::unique_ptr<Lock> locker_;
  Proto* proto_;

 private:
  void initialize() {
    locker_.reset(new Lock(data_->lock_));
    proto_ = dynamic_cast<Proto*>(data_->message_.get());
  }
};

}  // namespace data
}  // namespace rec
