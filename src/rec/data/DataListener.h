#ifndef __REC_DATA_DATALISTENER__
#define __REC_DATA_DATALISTENER__

#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

class Data;

template <typename Proto>
class DataListener : public Listener<const Proto&> {
 public:
  explicit DataListener() { adaptor_.reset(new Adaptor(this)); }
  virtual ~DataListener() {}

  virtual void operator()(const Proto&) = 0;
  Data* getData() const { return adaptor_->getData(); }
  const Proto getProto() const { return data::getProto<Proto>(getData()); }
  void setProto(const Proto& p) { setWithData(getData(), p); }

  virtual void startListening() {
    startListening(FILE_SCOPE);
  }

  void startListening(Scope scope) {
    adaptor_->startListening(scope);
  }

 private:
  class Adaptor : public UntypedDataListener {
   public:
    Adaptor(DataListener<Proto>* p) : UntypedDataListener(getTypeName<Proto>()),
                                      parent_(p) {
    }
    virtual ~Adaptor() {}

    virtual void operator()(const Message& m) {
      Lock l(this->lock_);
      if (const Proto* p = dynamic_cast<const Proto*>(&m))
        (*parent_)(*p);
      else
        LOG(DFATAL) << getTypeName(m) << " isn't type " << getTypeName<Proto>();
    }

   private:
    DataListener<Proto>* const parent_;
  };

  ptr<Adaptor> adaptor_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};

template <typename Proto>
class GlobalDataListener : public DataListener<Proto> {
 public:
  GlobalDataListener() {}
  virtual ~GlobalDataListener() {}

  virtual void startListening() {
    DataListener<Proto>::startListening(GLOBAL_SCOPE);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(GlobalDataListener);
};

}  // namespace data

using data::DataListener;
using data::GlobalDataListener;

}  // namespace rec

#endif  // __REC_DATA_DATALISTENER__
