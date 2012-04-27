#include "rec/gui/layout/Layout.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

Layout::Layout(const String& name,
               Orientation o,
               bool resizeOther)
    : Component(name),
      SizeHintAccumulator(o),
      orientation_(o),
      resizeOtherDimension_(resizeOther),
      cache_(NULL) {
}

void Layout::addToLayout(Component* c) {
  if (HasSizeHints* h = dynamic_cast<HasSizeHints*>(c))
    addToLayout(c, h->size(MIN), h->size(MAX), h->size(PREF));
  else
    addToLayout(c, DEFAULT_MIN, DEFAULT_MAX, DEFAULT_PREF);
}

void Layout::addToLayout(Component* c, double min, double max, double pref) {
  accumulate(min, max, pref);
  layoutManager_.setItemLayout(components_.size(), min, max, pref);
  components_.push_back(c);

  MessageManagerLock l;  // TODO: is this needed?
  addAndMakeVisible(c);
}

void Layout::resized() {
  Component::resized();
  layout();
}

void Layout::layout() {
  if (components_.size()) {
    layoutManager_.layOutComponents(&components_[0], components_.size(),
                                    0, 0, getWidth(), getHeight(),
                                    orientation_ == VERTICAL, 
									resizeOtherDimension_);
    if (cache_)
      cache_->invalidateAll();
  }
}

}  // namespace gui
}  // namespace rec
