#ifndef __REC_UTIL_UNTYPEDDATALISTENER__
#define __REC_UTIL_UNTYPEDDATALISTENER__

#include "rec/data/proto/Address.pb.h"
#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/util/Listener.h"

namespace rec {
namespace data {

class UntypedDataListener : public Listener<const Message&>,
                            public Listener<const VirtualFile&> {
 public:
  typedef AddressProto::Scope Scope;
  explicit UntypedDataListener(const string& typeName,
                               Scope scope = AddressProto::FILE_SCOPE);
  virtual ~UntypedDataListener();

  virtual void operator()(const Message& m) = 0;
  virtual void operator()(const VirtualFile&);

  const string& typeName() const { return typeName_; }
  Data* getData() const { Lock l(lock_); return data_; }

  static void setGlobalDataFile(const VirtualFile&);
  void updateCallback();

 protected:
  CriticalSection lock_;

 private:
  const Scope scope_;
  const string typeName_;
  Data* data_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedDataListener);
};

class UntypedGlobalDataListener : public UntypedDataListener {
 public:
  explicit UntypedGlobalDataListener(const string& typeName)
      : UntypedDataListener(typeName, AddressProto::GLOBAL_SCOPE) {
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedGlobalDataListener);
};

}  // namespace data

using data::UntypedDataListener;
using data::UntypedGlobalDataListener;

}  // namespace rec

#endif  // __REC_UTIL_UNTYPEDDATALISTENER__
