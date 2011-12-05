#ifndef __REC_GUI_LAYOUT_LAYOUT__
#define __REC_GUI_LAYOUT_LAYOUT__

#include <vector>

#include "rec/gui/Geometry.h"
#include "rec/gui/SizeAccumulator.h"

namespace rec {
namespace gui {

class Layout : public Component {
 public:
  enum SizeHint { MIN, MAX, PREF, LAST };

  Layout(const String& name = String::empty,
         Orientation o = HORIZONTAL,
         bool resizeOther = true)
      : Component(name),
        orientation_(o),
        resizeOtherDimension_(resizeOther) {
  }

  void setOrientation(Orientation o) { orientation_ = o; }
  Orientation orientation() const { return orientation_; }

  void addToLayout(Component* c) {
    if (Layout* layout = dynamic_cast<Layout*>(c))
      addToLayout(c, layout->size(MIN), layout->size(MAX), layout->size(PREF));
    else
      addToLayout(c, 12, -1.0, -1.0);
  }

  void addToLayout(Component* c, double m) { addToLayout(c, m, m, m); }

  void addToLayout(Component* c, double min, double max, double pref) {
    sizeHints_[MIN].accumulate(min);
    sizeHints_[MAX].accumulate(max);
    sizeHints_[PREF].accumulate(pref);
    layoutManager_.setItemLayout(components_.size(), min, max, pref);
    components_.push_back(c);
    MessageManagerLock l;
    addAndMakeVisible(c);
  }

  int size() const { return components_.size(); }

  int size(SizeHint hint) { return sizeHints_[hint].getSize(); }

  virtual void resized() {
    Component::resized();
    layout();
  }

  StretchableLayoutManager* layoutManager() { return &layoutManager_; }

 protected:
  virtual void layout() {
    layoutManager_.layOutComponents(&components_[0], components_.size(),
                                    0, 0, getWidth(), getHeight(),
                                    orientation_, resizeOtherDimension_);
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
