#ifndef __REC_GUI_DISABLEMAP__
#define __REC_GUI_DISABLEMAP__

#include <unordered_map>
#include <unordered_set>

#include "rec/gui/DisableableComponent.h"

namespace rec {
namespace gui {

class DisableMap {
 public:
  DisableMap() : disabled_(false) {}

  void addComponent(DisableableComponent*);
  void setProperty(const string&, bool);
  void setDisabled(bool isDisabled);

 private:
  void disable(DisableableComponent* comp, bool isDisabled);

  PropertyMap propertyMap_;
  std::unordered_multimap<string, DisableableComponent*> componentMap_;
  std::unordered_set<DisableableComponent*> components_;
  bool disabled_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DisableMap);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DISABLEMAP__
