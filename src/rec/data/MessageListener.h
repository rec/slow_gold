#ifndef __REC_DATA_MESSAGELISTENER__
#define __REC_DATA_MESSAGELISTENER__

#include "rec/util/Listener.h"

namespace rec {
namespace data {


template <typename Proto>
bool apply(Function f, Data* data) {
  return Applier<Proto>(data).apply(function));
}


  Applier tdl(data);

  Lock l(data->lock());

  ptr<Message> message(data->getMessage());
  if (Proto* proto = dynamic_cast<Proto*>(message.get()))
    return function(proto) && setMessage(*message);

  LOG(DFATAL) << getTypeName<Proto> << "!= " << getTypeName(*message);
  return false;
}



typedef Listener<const Message&> DataListener;

inline void swap(DataListener* ml, DataBroadcaster

class DataListener :  {
 public:
  DataListener() : data_(NULL) {}
  virtual ~DataListener() {}

  virtual void operator()(const Message&) = 0;

  virtual void setBroadcaster(DataBroadcaster* b) {
    Lock l(listenerLock_);
    if (broadcaster_)
      broadcaster_.removeListener(this);

    broadcaster_ = b;

    if (broadcaster_)
      broadcaster_.addListener(this);
  }

 private:
  Data* data_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_MESSAGELISTENER__
