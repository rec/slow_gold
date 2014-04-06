#include "rec/gui/proto/Panel.h"

#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Size.pb.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

Panel::Panel(const String& name,
             Orientation o,
             bool resizeOther,
             bool isMain,
             bool isOpaque)
    : Component(name),
      SizeHintAccumulator(o),
      orientation_(o),
      resizeOtherDimension_(resizeOther),
      cache_(nullptr),
      isMain_(isMain),
      isOpaque_(isOpaque) {
  DCHECK(not name.isEmpty());
}

Panel::~Panel() {
  deleteAllChildren();
}

void Panel::addToPanel(Component* c) {
  if (HasSizeHints* h = dynamic_cast<HasSizeHints*>(c))
    addToPanel(c, h->size(MIN), h->size(MAX), h->size(PREF));
  else
    addToPanel(c, DEFAULT_MIN, DEFAULT_MAX, DEFAULT_PREF);
}

void Panel::addToPanel(Component* c, double min, double max, double pref) {
  DCHECK(not c->getParentComponent());  // Can't move items around.
  accumulate(min, max, pref);
  layoutManager_.setItemLayout(components_.size(), min, max, pref);
  components_.push_back(c);

  addAndMakeVisible(c);
}

void Panel::addToPanel(
    Component* c, const Constants& constants, const Size& size) {
  float min, max, preferred;
  if (size.has_fixed()) {
    min = max = preferred = constants.getDouble(size.fixed());
  } else {
    min = constants.getDouble(size.min());
    max = constants.getDouble(size.max());
    preferred = constants.getDouble(size.preferred());
  }
  addToPanel(c, min, max, preferred);
}

void Panel::resized() {
  Component::resized();
  layout();
}

void Panel::layout() {
  int width = getWidth();
  int height = getHeight();
  if (components_.size() && width && height) {
    layoutManager_.layOutComponents(
        &components_[0], components_.size(),
        0, 0, width, height,
        orientation_ == VERTICAL, resizeOtherDimension_);
    if (cache_)
      cache_->invalidateAll();
  }
  repaint();
}

void Panel::clear(bool free) {
  SizeHintAccumulator::clear();
  layoutManager_.clearAllItems();
  components_.clear();
  while (uint size = getNumChildComponents()) {
    Component* c = getChildComponent(size - 1);
    removeChildComponent(c);
    if (free)
      delete c;
  }
}

}  // namespace gui
}  // namespace rec
