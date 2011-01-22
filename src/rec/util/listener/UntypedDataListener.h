#ifndef __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__

#include "rec/util/Reference.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace listener {

class UntypedDataListener : public Reference<persist::UntypedData>,
                            public Listener<const Message&> {
 public:
  typedef persist::UntypedData UntypedData;

  UntypedDataListener() {}
  virtual ~UntypedDataListener() {}
  virtual void operator()(const Message&) = 0;

  virtual void setData(UntypedData* d) {
    if (getData())
      getData()->messageBroadcaster()->removeListener(this);

    Reference<UntypedData>::setData(d);

    if (getData())
      getData()->messageBroadcaster()->addListener(this);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(UntypedDataListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
