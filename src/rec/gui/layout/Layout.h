#ifndef __REC_GUI_LAYOUT_LAYOUT__
#define __REC_GUI_LAYOUT_LAYOUT__

#include <vector>

#include "rec/gui/Geometry.h"
#include "rec/gui/SizeHintAccumulator.h"

namespace rec {
namespace gui {

class Layout : public Component, public SizeHintAccumulator,
               public SettableTooltipClient {
 public:
  static const int DEFAULT_MIN = 12;
  static const int DEFAULT_MAX = -1;
  static const int DEFAULT_PREF = -1;

  Layout(const String& name = String::empty,
         Orientation o = HORIZONTAL,
         bool resizeOther = true)
      : Component(name),
        SizeHintAccumulator(o),
        orientation_(o),
        resizeOtherDimension_(resizeOther) {
  }

  void setOrientation(Orientation o) { orientation_ = o; }
  Orientation orientation() const { return orientation_; }

  void addToLayout(Component* c) {
    if (HasSizeHints* h = dynamic_cast<HasSizeHints*>(c))
      addToLayout(c, h->size(MIN), h->size(MAX), h->size(PREF));
    else
      addToLayout(c, DEFAULT_MIN, DEFAULT_MAX, DEFAULT_PREF);
  }

   void addToLayout(Component* c, double m) {
     addToLayout(c, m, m, m);
   }

  void addToLayout(Component* c, double min, double max, double pref) {
    accumulate(min, max, pref);
    layoutManager_.setItemLayout(components_.size(), min, max, pref);
    components_.push_back(c);
    MessageManagerLock l;
    addAndMakeVisible(c);
  }

  int size() const { return components_.size(); }

  virtual void resized() {
    Component::resized();
    layout();
  }

  StretchableLayoutManager* layoutManager() { return &layoutManager_; }

 protected:
  virtual void layout() {
	if (components_.size()) {
      layoutManager_.layOutComponents(&components_[0], components_.size(),
                                      0, 0, getWidth(), getHeight(),
                                      orientation_, resizeOtherDimension_);
	}
  }

  StretchableLayoutManager layoutManager_;
  std::vector<Component*> components_;
  Orientation orientation_;
  const bool resizeOtherDimension_;
  SizeAccumulator sizeHints_[LAST];

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Layout);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LAYOUT_LAYOUT__
