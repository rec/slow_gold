#ifndef __REC_GUI_LAYOUT__
#define __REC_GUI_LAYOUT__

#include <vector>

#include "rec/base/base.h"
#include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

class Layout : public Component {
 public:
  Layout(Orientation o, bool resizeOther, const String& name = String::empty)
      : Component(name), orientation_(o), resizeOtherDimension_(resizeOther) {}

  void addToLayout(Component* c, double m) {
    addToLayout(c, m, m, m);
  }

  void addToLayout(Component* c, double min, double max, double pref) {
    layoutManager_.setItemLayout(components_.size(), min, max, pref);
    components_.push_back(c);
    addAndMakeVisible(c);
  }

  virtual void resized() {
    Component::resized();
    layout();
  }

  juce::StretchableLayoutManager* layoutManager() { return &layoutManager_; }

 protected:
  void layout() {
    layoutManager_.layOutComponents(&components_[0], components_.size(),
                                    0, 0, getWidth(), getHeight(),
                                    orientation_, resizeOtherDimension_);
  }

  juce::StretchableLayoutManager layoutManager_;
  std::vector<Component*> components_;
  const Orientation orientation_;
  const bool resizeOtherDimension_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Layout);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LAYOUT__
