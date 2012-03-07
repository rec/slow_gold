#include "rec/gui/layout/Layout.h"

namespace rec {
namespace gui {

Layout::Layout(const String& name,
               Orientation o,
               bool resizeOther)
    : Component(name),
      SizeHintAccumulator(o),
      orientation_(o),
      resizeOtherDimension_(resizeOther) {
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
  MessageManagerLock l;
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
                                    orientation_, resizeOtherDimension_);
  }
}

}  // namespace gui
}  // namespace rec
