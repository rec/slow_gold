#ifndef __REC_UTIL_UNTYPEDDATALISTENER__
#define __REC_UTIL_UNTYPEDDATALISTENER__

#include "rec/base/base.h"

namespace rec {
namespace util {

class UntypedDataListener : public Listener<const Message&>,
                            public Listener<const VirtualFile&>,
                            public UpdateRequester {
 public:
  UntypedDataListener(const string& typeName,
                      const data::Address& address =
                      data::Address::default_instance(),
                      bool isGlobal = false);

  virtual void requestUpdates();

  virtual void operator()(const Message&);
  virtual void operator()(const VirtualFile&);

 protected:
  virtual void setData(data::UntypedEditable* d);
  virtual void onDataChange();

 private:
  const data::Address address_;
  const bool isGlobal_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedDataListener);
};


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UNTYPEDDATALISTENER__
