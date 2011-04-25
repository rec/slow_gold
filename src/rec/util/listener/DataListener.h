#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/Data.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace util {
namespace listener {

// DataListener listens to changes in peristent data.

template <typename Proto>
class DataListener : public Listener<const Proto&> {
 public:
  DataListener() : data_(NULL) {}
  virtual ~DataListener() { setData(NULL); }
  virtual void operator()(const Proto& p) = 0;

  virtual void setData(persist::Data<Proto>* d) {
    if (data_ != d) {
      if (data_)
        data_->removeListener(this);

      data_ = d;

      if (data_)
        this->data_->addListener(this);
    }
  }

 private:
  persist::Data<Proto>* data_;

  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
