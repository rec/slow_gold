#ifndef __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/UntypedData.h"
#include "rec/data/Address.h"

namespace rec {
namespace util {
namespace listener {

// A ProtoListener has a view, a local copy of a persistent protocol buffer.
//
class ProtoListener : public Listener<const Message&>,
                      public Listener<data::UntypedData*> {
 public:
  ProtoListener(const data::Address& a) : address_(a), data_(NULL) {}

  virtual ~ProtoListener() {}
  virtual void operator()(const Message&);
  virtual const data::Address& address() const { return address_; }

  void setData(data::UntypedData* data);
  data::UntypedData* getData() { return data_; }
  virtual void operator()(data::UntypedData* data) { setData(data); }

 protected:
  // updatePersistentData is called when the local view of the data is changed
  // by the GUI, to update the persistent data.
  virtual void updatePersistentData();

  // Gets the data from the view.
  virtual const data::Value getDisplayValue() const = 0;

  // Set the view data when the persistent value has changed to update the local
  // data.
  virtual void setDisplayValue(const data::Value&) = 0;

 private:
  const data::Address address_;
  data::UntypedData* data_;

  DISALLOW_COPY_AND_ASSIGN(ProtoListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
