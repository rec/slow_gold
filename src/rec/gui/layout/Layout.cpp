#include "rec/gui/layout/Layout.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

namespace {

typedef juce::Rectangle<int> Rect;


class LayoutCache : public juce::CachedComponentImage {
 public:
  LayoutCache(std::vector<Component*>* c) : components_(c) {}

  virtual ~LayoutCache() {
    stl::deletePointers(&dirtyRectangles_);
  }

  virtual void paint(Graphics& g) {
    for (int i = 0; i < dirtyRectangles_.size(); ++i) {
      if (Rect* r = dirtyRectangles_[i]) {
        if (!r->isEmpty()) {
          Component* c = (*components_)[i];
          Graphics::ScopedSaveState ss(g);
          if (g.reduceClipRegion(*r)) {
            g.setOrigin(c->getX(), c->getY());
            c->paint(g);
          }
        }
      }
    }
  }

  /** Invalidates all cached image data. */
  virtual void invalidateAll() {
    for (int i = 0; i < dirtyRectangles_.size(); ++i) {
      if (Rect* r = dirtyRectangles_[i])
        *r = Rect();
    }
  }

  /** Invalidates a section of the cached image data. */
  virtual void invalidate (const Rect& area) {
    for (int i = 0; i < components_->size(); ++i) {
      Rect dirty = (*components_)[i]->getBounds().getIntersection(area);
      if (!dirty.isEmpty()) {
        if (i >= dirtyRectangles_.size())
          dirtyRectangles_.resize(i + 1);
        if (Rect* r = dirtyRectangles_[i])
          *r = r->getUnion(dirty);
         else
          dirtyRectangles_[i] = new Rect(dirty);
      }
    }
  }

  virtual void releaseResources() {}

 private:
  std::vector<Component*>* components_;
  std::vector<Rect*> dirtyRectangles_;
};

}  // namespace

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
    if (cache_)
      cache_->invalidateAll();
  }
}

void Layout::useCachedComponent() {
  cache_ = new LayoutCache(&components_);
  setCachedComponentImage(cache_);
}

}  // namespace gui
}  // namespace rec
