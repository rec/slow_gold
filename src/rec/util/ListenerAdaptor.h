#ifndef __REC_UTIL_LISTENERADAPTOR__
#define __REC_UTIL_LISTENERADAPTOR__

#include "rec/util/MessageListener.h"

namespace rec {
namespace util {

template <typename Type1, typename Type2 = const Message&>
class ListenerAdaptor : public Listener<Type1> {
 public:
  ListenerAdaptor() : adaptor_(this) {}
  virtual ~ListenerAdaptor() {}

  Listener<Type2>* adaptor() { return &adaptor_; }

 private:
  class Adaptor : public Listener<Type2> {
   public:
    explicit Adaptor(ListenerAdaptor<Type1, Type2>* p) : parent_(p) {}
    virtual ~Adaptor() {}

    virtual void operator()(Type1 t1) {
      if (Type2 t2 = dynamic_cast<Type2>(&t1))
        (*parent_)(*t2);
      else
        LOG(DFATAL) << getTypeName(t1) << " should be " << getTypeName<Type1>();
    }

   private:
    ListenerAdaptor<Type1, Type2>* parent_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Adaptor);
  };

 private:
  Adaptor adaptor_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageListener);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENERADAPTOR__
