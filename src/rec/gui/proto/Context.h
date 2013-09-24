#ifndef __REC_GUI_PROTO_CONTEXT__
#define __REC_GUI_PROTO_CONTEXT__

#include "rec/base/base.h"

namespace rec {
namespace gui {

struct Context {
  Context(const ComponentProto& component, const Constants& constants,
          Component* parent)
      : component_(component), constants_(constants), parent_(parent) {
  }

  const ComponentProto& component_;
  const Constants& constants_;
  Component* parent_;
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_CONTEXT__
