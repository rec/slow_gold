#ifndef __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/UntypedData.h"

namespace rec {
namespace util {
namespace listener {

// A ProtoListener has a view, a local copy of a persistent protocol buffer.
//
class ProtoListener : public Listener<const Message&> {
 public:
  typedef proto::arg::Address Address;
  ProtoListener(const Address& a) : address_(a), data_(NULL) {}

  virtual ~ProtoListener() {}
  virtual void operator()(const Message&);
  virtual const Address& address() const { return address_; }

  void setData(persist::UntypedData* data);
  persist::UntypedData* getData() { return data_; }

 protected:
  // onChange is called when the local view of the data is changed by the GUI,
  // to update the persistent data.
  virtual void updatePersistentData();

  // Gets the data from the view.
  virtual const Value getDisplayValue() const = 0;

  // Set the view data.
  virtual void setDisplayValue(const Value&) = 0;

 private:
  const Address address_;
  persist::UntypedData* data_;

  DISALLOW_COPY_AND_ASSIGN(ProtoListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
