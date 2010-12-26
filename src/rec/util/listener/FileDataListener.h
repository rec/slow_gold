#ifndef __REC_UTIL_LISTENER_FILEDATALISTENER__
#define __REC_UTIL_LISTENER_FILEDATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/Data.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class FileDataListener : public Listener<const Proto&> {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  explicit FileDataListener(const Address& address,
                            const string& name)
      : address_(address), name_(name), data_(NULL) {
  }

  ~FileDataListener() { setData(NULL); }

  virtual void operator()(const Proto& message) {
    set(proto::getValue(address_, message));
    onChanged();
  }

  Data* data() { return data_; }
  const Address& address() const { return address_; }

  void setData(Data* data) {
    if (data_)
      data_->removeListener(this);

    data_ = data;

    if (data_) {
      data_->addListener(this);
      (*this)(data_->get());
    }
  }

 protected:
  virtual const Value get() const = 0;
  virtual void set(const Value&) = 0;

  virtual void onChanged() {
    if (data_)
      data_->setter()->set(address_, get());
    else
      LOG(ERROR) << "No data but got a change on "
                 << persist::getProtoName<Proto>();
  }

 private:
  const Address address_;
  const string name_;
  Data* data_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FileDataListener);
};


}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_FILEDATALISTENER__
