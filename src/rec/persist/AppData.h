#ifndef __REC_PERSIST_APPDATA__
#define __REC_PERSIST_APPDATA__

#include <string>

#include "rec/persist/AutosaveApp.h"

namespace rec {
namespace persist {

inline App* createInstance(const String& name, int frequency, int priority) {
  static App* app = new AutosaveApp(name, frequency, priority);
  return app;
}

inline App* getInstance() {
  return createInstance(String(""), 0, 0);
    
  // Parameters won't be seen assuming the full version of getInstance has
  // already been called!
}  
  
template <typename Proto>
Data<Proto>* getAppData(const std::string& name) {
  return getInstance()->getData<Proto>(name);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPDATA__
