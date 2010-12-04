#ifndef __REC_WIDGET_WIDGET__
#define __REC_WIDGET_WIDGET__

#include "rec/base/base.h"

namespace rec {
namespace widget {

template <typename Proto, typename Comp>
struct Widget {
  Widget(const Proto& desc, Comp* comp) : desc_(desc), component_(comp) {}

  Proto desc_;
  scoped_ptr<Comp> component_;

  void addToParent(Component* parent) {
    const gui::Layer& layer = desc_.widget().layer();
    parent->addChildComponent(component_.get(), layer.zOrder());

    const gui::Rectangle &b = layer.bounds();
    component_.get()->setBounds(b.top_left().x(), b.top_left().y(),
                                b.dimensions().width(),
                                b.dimensions().height());
    return widget;
  }
};

}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WIDGET__
