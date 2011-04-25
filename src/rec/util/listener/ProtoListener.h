#ifndef __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__

#include "rec/util/Reference.h"
#include "rec/util/listener/Listener.h"
#include "rec/data/persist/UntypedData.h"

namespace rec {
namespace util {
namespace listener {

class ProtoListener : public Reference<persist::UntypedData>,
                      public Listener<const Message&> {
 public:
  ProtoListener() {}
  virtual ~ProtoListener() {}
  virtual void operator()(const Message&) = 0;

  virtual void setData(persist::UntypedData* data) {
    if (getData())
      getData()->messageBroadcaster()->removeListener(this);

    Reference<persist::UntypedData>::setData(data);

    if (data) {
      data->messageBroadcaster()->addListener(this);
      ptr<Message> m(data->clone());
      (*this)(*m);
    }
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(ProtoListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
