#ifndef __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/UntypedData.h"

namespace rec {
namespace util {
namespace listener {

class ProtoListener : public Listener<const Message&> {
 public:
  ProtoListener() : data_(NULL) {}
  virtual ~ProtoListener() {}
  virtual void operator()(const Message&) = 0;

  void setData(persist::UntypedData* data) {
    if (data_)
      data_->messageBroadcaster()->removeListener(this);

    data_ = data;

    if (data_) {
      data_->messageBroadcaster()->addListener(this);
      (*this)(*ptr<Message>(data_->clone()));
    }
  }

  persist::UntypedData* getData() { return data_; }

 private:
  persist::UntypedData* data_;

  DISALLOW_COPY_AND_ASSIGN(ProtoListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
