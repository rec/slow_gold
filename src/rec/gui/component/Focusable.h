#ifndef __REC_GUI_COMPONENT_FOCUSABLE__
#define __REC_GUI_COMPONENT_FOCUSABLE__

#include "rec/base/base.h"

namespace rec {
namespace gui {
namespace component {

template <typename Type = Component>
class Focusable : public Type {
 public:
  Focusable() {}
  virtual ~Focusable() { this->setWantsKeyboardFocus(true); }
  virtual void focusGained(Component::FocusChangeType) { this->repaint(); }
  virtual void focusLost(Component::FocusChangeType) { this->repaint(); }
  virtual void paintFocus(Graphics& g) {
    if (this->hasKeyboardFocus(true) || Component::getCurrentlyFocusedComponent() == this) {
      g.setColour(juce::Colours::red.withAlpha(0.8f));
      g.drawRect(this->getLocalBounds());
    }
  }

  virtual void paintOverChildren(Graphics& g) { paintFocus(g); }

 private:
  DISALLOW_COPY_AND_ASSIGN(Focusable);
};

}  // namespace component
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COMPONENT_FOCUSABLE__
