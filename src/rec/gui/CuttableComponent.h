#ifndef __REC_GUI_CUTTABLECOMPONENT__
#define __REC_GUI_CUTTABLECOMPONENT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class CuttableComponent : public Component {
 public:
  CuttableComponent(const String& name = String::empty) : Component("cut-" + name) {}

  static CuttableComponent* make(Component* comp) {
    return comp->getName().startsWith("cut-") ?
      dynamic_cast<CuttableComponent*>(comp): NULL;
  }

  virtual bool canCopy() const { return false; }
  virtual string copy() const { return ""; }
  virtual string cut() { return ""; }
  virtual bool paste(const string&) const { return false; }

  static bool cutToClipboard(Component* comp);
  static bool copyToClipboard(Component* comp);
  static bool pasteToClipboard(Component* comp);

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CuttableComponent);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_CUTTABLECOMPONENT__
