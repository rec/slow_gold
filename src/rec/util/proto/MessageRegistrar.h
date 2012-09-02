#ifndef __REC_DATA_MESSAGEREGISTRAR__
#define __REC_DATA_MESSAGEREGISTRAR__

#include "rec/base/base.h"

namespace rec {
namespace util {

class MessageRegistrar {
 public:
  MessageRegistrar() {}
  virtual ~MessageRegistrar() {}

  virtual void registerInstance(const Message& m, bool copy = true) = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageRegistrar);
};

template <typename Class>
void registerClass(MessageRegistrar* registrar) {
  registrar->registerInstance(Class::default_instance(), false);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_DATA_MESSAGEREGISTRAR__
