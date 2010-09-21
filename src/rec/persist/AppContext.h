#ifndef __REC_PERSIST_APPCONTEXT__
#define __REC_PERSIST_APPCONTEXT__

#include "rec/base/basictypes.h"

namespace rec {
namespace persist {

// Created at the start of the application, destroyed at the end.
// Contains all the threads.
class AppContext {
 public:
  AppContext() {}

  void someMethod() {
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(AppContext);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPCONTEXT__
