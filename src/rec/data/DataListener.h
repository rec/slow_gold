#ifndef __REC_DATA_DATALISTENER__
#define __REC_DATA_DATALISTENER__

#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/Undoable.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/Address.pb.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

class Data;

template <typename Proto>
class DataListener : public Listener<const Proto&> {
 public:
  typedef AddressProto::Scope Scope;

  explicit DataListener() : adaptor_(new Adaptor(this)) {}
  virtual ~DataListener() {}

  virtual void operator()(const Proto&) = 0;
  Data* getData() const { return adaptor_->getData(); }

  const Proto getDataValue() const {
    if (Data* data = getData())
      return data::getProto<Proto>(data);
    else
      return Proto();
  }

  void setProto(const Proto& p, Undoable undoable = CAN_UNDO) {
    if (Data* data = getData())
      data::setProto(p, data, undoable);
    else
      LOG(DFATAL) << "No data";
  }

  void updateCallback() {
    adaptor_->updateCallback();
  }

 private:
  class Adaptor : public UntypedDataListener {
   public:
    Adaptor(DataListener<Proto>* p)
        : UntypedDataListener(getTypeName<Proto>()), parent_(p) {
    }

    virtual void operator()(const Message& m) {
      Lock l(this->lock_);
      if (const Proto* p = dynamic_cast<const Proto*>(&m))
        (*parent_)(*p);
      else
        LOG(DFATAL) << getTypeName(m) << " isn't type " << getTypeName<Proto>();
    }
    virtual ~Adaptor() {}

   private:
    DataListener<Proto>* const parent_;
  };

  ptr<Adaptor> adaptor_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};

}  // namespace data

using data::DataListener;

}  // namespace rec

#endif  // __REC_DATA_DATALISTENER__
