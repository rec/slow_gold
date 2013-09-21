#ifndef __REC_DATA_MESSAGEREGISTRAR__
#define __REC_DATA_MESSAGEREGISTRAR__

#include "rec/base/base.h"
#include "rec/data/proto/Address.pb.h"

namespace rec {
namespace util {

class MessageRegistrar {
 public:
  MessageRegistrar() {}
  virtual ~MessageRegistrar() {}

  virtual void registerInstance(
      const Message& m, bool copy, data::AddressProto::Scope) = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageRegistrar);
};

template <typename Class>
void registerLocal(MessageRegistrar* registrar) {
  registrar->registerInstance(Class::default_instance(), false,
                              data::AddressProto::FILE_SCOPE);
}

template <typename Class>
void registerGlobal(MessageRegistrar* registrar) {
  registrar->registerInstance(Class::default_instance(), false,
                              data::AddressProto::GLOBAL_SCOPE);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_DATA_MESSAGEREGISTRAR__
