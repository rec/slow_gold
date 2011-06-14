#ifndef __REC_GUI_LAYOUT_LAYOUT__
#define __REC_GUI_LAYOUT_LAYOUT__

#include <vector>

#include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

class Layout : public Component {
 public:
  Layout(const String& name = String::empty,
         Orientation o = HORIZONTAL,
         bool resizeOther = true)
      : Component(name),
	    orientation_(o),
	    resizeOtherDimension_(resizeOther) {
  }

  void setOrientation(Orientation o) { orientation_ = o; }
  Orientation orientation() const { return orientation_; }

  void addToLayout(Component* c)           { addToLayout(c, 1, -1.0, -1.0); }
  void addToLayout(Component* c, double m) { addToLayout(c, m, m, m); }

  void addToLayout(Component* c, double min, double max, double pref) {
    layoutManager_.setItemLayout(components_.size(), min, max, pref);
    components_.push_back(c);
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
    layoutManager_.layOutComponents(&components_[0], components_.size(),
                                    0, 0, getWidth(), getHeight(),
                                    orientation_, resizeOtherDimension_);
  }

  StretchableLayoutManager layoutManager_;
  std::vector<Component*> components_;
  Orientation orientation_;
  const bool resizeOtherDimension_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Layout);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LAYOUT_LAYOUT__
