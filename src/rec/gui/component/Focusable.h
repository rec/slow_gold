#ifndef __REC_GUI_COMPONENT_FOCUSABLE__
#define __REC_GUI_COMPONENT_FOCUSABLE__

#include "rec/base/base.h"

namespace rec {
namespace gui {
namespace component {

template <typename Type = Component>
class Focusable : public Type {
 public:
  explicit Focusable(ApplicationCommandManager* m = NULL) : manager_(m) {
    this->setWantsKeyboardFocus(true);
  }

  void setManager(ApplicationCommandManager* m) { manager_ = m; }
  virtual ~Focusable() {}

  virtual void focusGained(Component::FocusChangeType) {
    if (manager_)
      manager_->commandStatusChanged();

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
  ApplicationCommandManager* manager_;

  DISALLOW_COPY_AND_ASSIGN(Focusable);
};

}  // namespace component
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COMPONENT_FOCUSABLE__
