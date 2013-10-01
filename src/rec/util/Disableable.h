#ifndef __REC_GUI_DISABLEABLECOMPONENT__
#define __REC_GUI_DISABLEABLECOMPONENT__

#include <unordered_map>
#include "rec/base/base.h"

namespace rec {
namespace util {

typedef std::unordered_map<string, bool> PropertyMap;

class Disableable {
 public:
  Disableable() {}
  virtual ~Disableable() {}

  template <typename Type>
  void addDisableProperties(Type properties) {
    Lock l(lock_);
    for (auto& p: properties)
      propertyMap_[p] = false;
  }

  void setDisableProperty(const string& name, bool value);
  bool getDisabledFromProperties() const;
  const PropertyMap& map() const { return propertyMap_; }

  void disable(bool isDisabled);

 private:
  CriticalSection lock_;
  PropertyMap propertyMap_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Disableable);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_GUI_DISABLEABLECOMPONENT__
