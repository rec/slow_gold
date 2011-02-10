#ifndef __REC_GUI_CUTTABLECOMPONENT__
#define __REC_GUI_CUTTABLECOMPONENT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class CuttableComponent : public Component {
 public:
  CuttableComponent(const String& name = String::empty) : Component("cut-" + name) {}

  virtual bool canCopy() const { return false; }
  virtual bool canPaste() const { return false; }
  virtual string copy() const { return ""; }
  virtual string cut() { return ""; }
  virtual bool paste(const string&) const { return false; }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CuttableComponent);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_CUTTABLECOMPONENT__
