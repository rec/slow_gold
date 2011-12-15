#ifndef __REC_DATA_MESSAGEREGISTRY__
#define __REC_DATA_MESSAGEREGISTRY__

#include "rec/base/base.h"

namespace rec {
namespace data {

class MessageRegistry {
 public:
  MessageRegistry() {}
  virtual ~MessageRegistry() {}

  virtual void registerInstance(const Message& m, bool copy = true) = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageRegistry);
};

template <typename Class>
void registerClass(MessageRegistry* registrar) {
  registrar->registerInstance(Class::default_instance(), false);
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_MESSAGEREGISTRY__
