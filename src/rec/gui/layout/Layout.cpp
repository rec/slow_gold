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

  addAndMakeVisible(c);
}

void Layout::resized() {
  Component::resized();
  layout();
}

void Layout::layout() {
  int width = getWidth();
  int height = getHeight();
  if (components_.size() && width && height) {
    layoutManager_.layOutComponents(&components_[0], components_.size(),
                                    0, 0, width, height,
                                    orientation_ == VERTICAL,
									resizeOtherDimension_);
    if (cache_)
      cache_->invalidateAll();
  }
}

void Layout::clear() {
  SizeHintAccumulator::clear();
  layoutManager_.clearAllItems();
  components_.clear();
  while (uint size = getNumChildComponents())
    removeChildComponent(getChildComponent(size - 1));
}

}  // namespace gui
}  // namespace rec
