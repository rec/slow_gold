#ifndef __REC_GUI_DISABLEABLECOMPONENT__
#define __REC_GUI_DISABLEABLECOMPONENT__

#include <unordered_map>
#include "rec/base/base.h"

namespace rec {
namespace gui {

typedef std::unordered_map<string, bool> PropertyMap;

class DisableableComponent {
 public:
  DisableableComponent() {}
  virtual ~DisableableComponent() {}

  template <typename Type>
  void addDisableProperties(Type properties) {
    Lock l(lock_);
    for (auto& p: properties)
      propertyMap_[p] = false;
  }

  void setDisableProperty(const string& name, bool value) {
    Lock l(lock_);
    propertyMap_[name] = value;
  }

  bool getDisabledFromProperties() const {
    Lock l(lock_);
    for (auto& i: propertyMap_) {
      if (i.second)
        return true;
    }
    return false;
  }

  const PropertyMap& map() const { return propertyMap_; }

 private:
  CriticalSection lock_;
  PropertyMap propertyMap_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DisableableComponent);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DISABLEABLECOMPONENT__
