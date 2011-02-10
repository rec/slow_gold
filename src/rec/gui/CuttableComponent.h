#ifndef __REC_GUI_CUTTABLECOMPONENT__
#define __REC_GUI_CUTTABLECOMPONENT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class CuttableComponent : public Component {
 public:
  CuttableComponent(const String& name = String::empty) : Component("cut-" + name) {}

  virtual bool canCopy() const { return false; }
  virtual string copy() const { return ""; }
  virtual string cut() { return ""; }
  virtual bool paste(const string&) const { return false; }

  static CuttableComponent* make(Component* comp);

  static bool cutToClipboard(Component* comp);
  static bool copyToClipboard(Component* comp);
  static bool pasteToClipboard(Component* comp);

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CuttableComponent);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_CUTTABLECOMPONENT__
