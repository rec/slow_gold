#ifndef __REC_DATA_ADDRESSLISTENER__
#define __REC_DATA_ADDRESSLISTENER__

#include "rec/data/Address.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/Value.h"
#include "rec/data/proto/FieldOps.h"

namespace rec {
namespace data {

class AddressListener : public UntypedDataListener, public Listener<Value> {
 public:
  AddressListener(const Address& a, const string& typeName, bool global = false)
      : UntypedDataListener(typeName, global), address_(a) {
  }
  virtual ~AddressListener() {}

  virtual void operator()(const Value&) = 0;
  virtual void operator()(const Message& m) {
    Value value;
    if (getValueWithAddress(address_, m, &value))
      (*this)(value);
    else
      LOG(DFATAL) << address_.ShortDebugString() << "|" << m.ShortDebugString();
  }

  virtual void setValue(const Value& v, bool undoable) const {
    Opener<Message> opener(getData(), undoable);
    if (!setValueWithAddress(address_, opener.get_mutable(), v))
      LOG(DFATAL) << address_.ShortDebugString() << "|" << v.ShortDebugString();
  }

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(AddressListener);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_ADDRESSLISTENER__
