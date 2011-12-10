#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/TypedEditable.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Listener.h"
#include "rec/util/UntypedDataListener.h"
#include "rec/util/UpdateRequester.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class DataListener : public Listener<const Proto&>,
                     public UntypedDataListener {
 public:
  DataListener(const data::Address& address =
               data::Address::default_instance(),
               bool isGlobal = false);
  virtual ~DataListener() {}

  virtual void operator()(const Proto&);

  void setProto(const Proto& p) { this->setValue(p); }
  const Proto getProto() const { return typedData_->get(); }
  virtual void setData(data::UntypedEditable* e);

 protected:
  virtual void onDataChange(const Proto&) {}

 private:
 	typedef data::TypedEditable<Proto> TypedEditable;

  data::TypedEditable<Proto>* typedData_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};


template <typename Proto>
class GlobalDataListener : public DataListener<Proto> {
 public:
  GlobalDataListener(const data::Address& address =
               data::Address::default_instance())
      : DataListener<Proto>(address, true) {
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(GlobalDataListener);
};

//
// Implementations
//

template <typename Proto>
DataListener<Proto>::DataListener(const data::Address& a, bool global)
    : UntypedDataListener(Proto::default_instance().GetTypeName(), a, global),
      typedData_(dynamic_cast<TypedEditable*>(this->data())) {
  DCHECK(typedData_) << "No typed data for " << typeName();
}

template <typename Proto>
void DataListener<Proto>::operator()(const Proto& p) {
  onDataChange(p);
  UntypedDataListener::onDataChange(p);
}

template <typename Proto>
void DataListener<Proto>::setData(data::UntypedEditable* e) {
  UntypedDataListener::setData(e);
  TypedEditable* typedData = dynamic_cast<TypedEditable*>(e);
  if (!typedData) {
    LOG(DFATAL) << "Bad data listener for " << this->typeName();
    return;
  }

  Lock l(UntypedDataListener::lock_);

  typedData_->removeListener(this);
  typedData_ = typedData;
  typedData_->addListener(this);
}

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
