#ifndef __REC_DATA_READER__
#define __REC_DATA_READER__

#include <google/protobuf/message.h>

#include "rec/data/Data.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
struct Reader {
  Reader(Data* d)
      : data_(d),
        locker_(new Lock(d->lock_)),
        proto_(dynamic_cast<Proto*>(d->message_.get())) {
  }

  ~Reader() {}

  const Proto& operator*() const { return get(); }
  const Proto* operator->() const { return &get(); }
  const Proto& get() const {
    return *proto_;
  }

  Message* newMessage() const {
    return clone(*proto_);
  }

 protected:
  Data* const data_;
  ptr<Lock> locker_;
  Proto* const proto_;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_READER__
