#ifndef __REC_GUI_COMPONENT__
#define __REC_GUI_COMPONENT__

#include "rec/base/base.h"
#include "rec/gui/Component.pb.h"

namespace rec {
namespace gui {

class ComponentDelegate {
 public:
  ComponentDelegate(const ComponentDesc* desc,
                    const ComponentDelegate* next = NULL)
      : desc_(desc), next_(next) {
  }

  const colors::Colors& colors() const {
    return (desc_ && desc_->has_colors()) ? desc->colors() : next->colors();
  }

  const FontDesc& font() const {
    return (desc_ && desc_->has_font()) ? desc->font() : next->font();
  }

  const int margin() const {
    return (desc_ && desc_->has_margin()) ? desc->margin() : next->margin();
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Component);
  ComponentDesc* desc_;
  ComponentDelegate* next_;
};


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COMPONENT__
