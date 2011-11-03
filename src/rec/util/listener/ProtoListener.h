#ifndef __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/UntypedEditable.h"
#include "rec/data/Address.h"

namespace rec {
namespace util {
namespace listener {

// A ProtoListener has a view, a local copy of a persistent protocol buffer.
//
class ProtoListener : public Listener<const Message&>,
                      public Listener<data::UntypedEditable*> {
 public:
  ProtoListener(const data::Address& a) : address_(a), untypedData_(NULL) {}

  virtual ~ProtoListener() {}
  virtual void operator()(const Message&);
  virtual const data::Address& address() const { return address_; }

  void setUntypedEditable(data::UntypedEditable* data);
  data::UntypedEditable* getUntypedEditable() { return untypedData_; }
  virtual void operator()(data::UntypedEditable* data) { setUntypedEditable(data); }

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
  data::UntypedEditable* untypedData_;

  DISALLOW_COPY_AND_ASSIGN(ProtoListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDDATALISTENER__
