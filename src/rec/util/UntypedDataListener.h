#ifndef __REC_UTIL_UNTYPEDDATALISTENER__
#define __REC_UTIL_UNTYPEDDATALISTENER__

#include "rec/data/Address.h"
#include "rec/util/Listener.h"
#include "rec/util/UpdateRequester.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {

namespace data { class UntypedEditable; }

namespace util {


class UntypedDataListener : public Listener<const Message&>,
                            public Listener<const VirtualFile&>,
                            public UpdateRequester {
 public:
  UntypedDataListener(const string& typeName,
                      const data::Address& address =
                      data::Address::default_instance(),
                      bool isGlobal = false);

  virtual ~UntypedDataListener() {}

  virtual void requestUpdates();

  virtual void operator()(const Message& m) { onDataChange(m); }
  virtual void operator()(const VirtualFile&);

 protected:
  virtual void setData(data::UntypedEditable* d);
  virtual void onDataChange(const Message&m);

 private:
  CriticalSection lock_;
  data::UntypedEditable* data_;
  const string typeName_;
  const data::Address address_;
  const bool isGlobal_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedDataListener);
};

class UntypedGlobalDataListener : public UntypedDataListener {
 public:
  explicit UntypedGlobalDataListener(const string& typeName,
                                     const data::Address& address =
                                     data::Address::default_instance())
      : UntypedDataListener(typeName, address, true) {
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedGlobalDataListener);
};


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UNTYPEDDATALISTENER__
