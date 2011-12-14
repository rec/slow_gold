#ifndef __REC_DATA_TYPEDLISTENER__
#define __REC_DATA_TYPEDLISTENER__

#include "rec/util/Listener.h"

namespace rec {
namespace data {

template <typename Proto>
class TypedListener : public Listener<const Proto&> {
 public:
  TypedListener() {
    adaptor_.parent_ = this;
  }
  virtual ~TypedListener() {}

  void setBroadcaster(MessageBroadcaster* b) {
    adaptor_.setBroadcaster(b);
  }

 private:
  struct Adaptor : public MessageListener {
    TypedListener<Proto>* parent_;

    virtual void operator()(const Message& m) {
      if (const Proto* proto = dynamic_cast<Proto*>(&m))
        (*parent_)(*proto);
      else
        LOG(DFATAL) << getTypeName<Proto>() << " should be " << getTypeName(m);
    }
  };

  Adaptor adaptor_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageListener);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_TYPEDLISTENER__
