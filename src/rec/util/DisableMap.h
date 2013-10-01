#ifndef __REC_GUI_DISABLEMAP__
#define __REC_GUI_DISABLEMAP__

#include <unordered_map>
#include <unordered_set>

#include "rec/util/Disableable.h"

namespace rec {
namespace util {

class DisableMap {
 public:
  DisableMap() : disabled_(false) {}
  virtual ~DisableMap() {}

  void addComponent(Disableable*);
  virtual bool setProperty(const string&, bool);
  bool getProperty(const string&) const;
  bool setDisabled(bool isDisabled);

 private:
  void disable(Disableable* comp, bool isDisabled);

  PropertyMap propertyMap_;
  std::unordered_multimap<string, Disableable*> componentMap_;
  std::unordered_set<Disableable*> components_;
  bool disabled_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DisableMap);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_GUI_DISABLEMAP__
