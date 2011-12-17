#ifndef __REC_DATA_DATALISTENER__
#define __REC_DATA_DATALISTENER__

#include "rec/data/UntypedDataListener.h"
#include "rec/util/Listener.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
class DataListener : public Listener<const Proto&> {
 public:
  explicit DataListener(bool isGlobal = false) : adaptor_(this, isGlobal) {}
  virtual ~DataListener() {}

  virtual void operator()(const Proto&) = 0;
  Data* getData() { return adaptor_.getData(); }

 private:
  class Adaptor : public UntypedDataListener {
   public:
    Adaptor(DataListener<Proto>* p, bool isGlobal)
        : UntypedDataListener(getTypeName<Proto>(), isGlobal),
          parent_(p) {
    }
    virtual ~Adaptor() {}

    virtual void operator()(const Message& m) {
      if (const Proto* p = dynamic_cast<const Proto*>(&m))
        (*parent_)(*p);
      else
        LOG(DFATAL) << getTypeName(m) << " isn't type " << getTypeName<Proto>;
    }

   private:
    DataListener<Proto>* const parent_;
  };

  Untyped adaptor_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};

template <typename Proto>
class GlobalDataListener : public DataListener<Proto> {
 public:
  GlobalDataListener() : DataListener<Proto>(true) {}
  virtual ~GlobalDataListener() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(GlobalDataListener);
};


}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATALISTENER__
