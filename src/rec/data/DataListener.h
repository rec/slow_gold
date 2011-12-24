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
  explicit DataListener(Scope scope = FILE_SCOPE) : adaptor_(this, scope) {}
  virtual ~DataListener() {}

  virtual void operator()(const Proto&) = 0;
  Data* getData() const { return adaptor_.getData(); }
  const Proto getProto() const { return data::getProto<Proto>(getData()); }
  void setProto(const Proto& p) { setWithData(getData(), p); }

 private:
  class Adaptor : public UntypedDataListener {
   public:
    Adaptor(DataListener<Proto>* p, Scope scope)
        : UntypedDataListener(getTypeName<Proto>(), scope),
          parent_(p) {
    }
    virtual ~Adaptor() {}

    virtual void operator()(const Message& m) {
      if (const Proto* p = dynamic_cast<const Proto*>(&m))
        (*parent_)(*p);
      else
        LOG(DFATAL) << getTypeName(m) << " isn't type " << getTypeName<Proto>();
    }

   private:
    DataListener<Proto>* const parent_;
  };

  Adaptor adaptor_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};

template <typename Proto>
class GlobalDataListener : public DataListener<Proto> {
 public:
  GlobalDataListener() : DataListener<Proto>(GLOBAL_SCOPE) {}
  virtual ~GlobalDataListener() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(GlobalDataListener);
};

}  // namespace data

using data::DataListener;
using data::GlobalDataListener;

}  // namespace rec

#endif  // __REC_DATA_DATALISTENER__
