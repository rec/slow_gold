#ifndef __REC_UTIL_UNTYPEDDATALISTENER__
#define __REC_UTIL_UNTYPEDDATALISTENER__

#include "rec/data/Address.h"
#include "rec/data/UntypedEditable.h"
#include "rec/data/Value.h"
#include "rec/util/Listener.h"
#include "rec/util/UpdateRequester.h"
#include "rec/util/file/VirtualFile.h"

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

  virtual ~UntypedDataListener() {}

  virtual void requestUpdates();

  virtual void operator()(const Message& m) { onDataChange(m); }
  virtual void operator()(const VirtualFile&);

  template <typename Type>
  void setValue(Type t, bool undoable = true) const {
    if (!isEmpty())
      data_->setValue(t, address_, undoable);
  }

  const data::Value getValue(const data::Address& addr =
                             data::Address::default_instance()) const {
    data::Value value;
    if (!isEmpty())
      value = data_->getValue(address_ + addr);
    return value;
  }

 protected:
  virtual void setData(data::UntypedEditable*);
  virtual void onDataChange(const Message&) {}
  const data::Address& address() const { return address_; }
  const string& typeName() const { return typeName_; }
  data::UntypedEditable* data() const { return data_; }
  Message* clone() const { return data_->clone(); }

  bool isEmpty() const { return data_->isEmpty(); }

  CriticalSection lock_;

 private:
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
