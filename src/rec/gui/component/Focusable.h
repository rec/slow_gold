#ifndef __REC_GUI_COMPONENT_FOCUSABLE__
#define __REC_GUI_COMPONENT_FOCUSABLE__

#include "rec/base/base.h"

namespace rec {
namespace gui {
namespace component {

template <typename Type = Component>
class Focusable : public Type {
 public:
  explicit Focusable(MenuBarModel* m) : menus_(m) {
    this->setWantsKeyboardFocus(true);
  }

  void setMenuBarModel(MenuBarModel* m) { menus_ = m; }

  virtual ~Focusable() {}

  virtual void focusGained(Component::FocusChangeType) {
    DLOG(INFO) << "Here!";
    menus_->menuItemsChanged();
#ifdef FOCUS_BUG_FIXED
    if (manager_)
      manager_->commandStatusChanged();
#endif

    this->repaint();
  }
  virtual void focusLost(Component::FocusChangeType t) { focusGained(t); }

  virtual void paintFocus(Graphics& g) {
    if (this->hasKeyboardFocus(true) || Component::getCurrentlyFocusedComponent() == this) {
      g.setColour(juce::Colours::red.withAlpha(0.8f));
      g.drawRect(this->getLocalBounds());
    }
  }

  virtual void paintOverChildren(Graphics& g) { paintFocus(g); }

 private:
  MenuBarModel* menus_;

  DISALLOW_COPY_AND_ASSIGN(Focusable);
};

}  // namespace component
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COMPONENT_FOCUSABLE__
