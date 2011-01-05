#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/Data.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class DataListener : public Listener<const Proto&> {
 public:
  typedef persist::Data<Proto> Data;

  DataListener() : data_(NULL) {}

  virtual ~DataListener() { setData(NULL); }

  Data* data() { return data_; }

  virtual void setData(Data* data) {
    if (data_)
      data_->removeListener(this);

    data_ = data;

    if (data_)
      data_->addListener(this);
  }

 private:
  Data* data_;

  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
