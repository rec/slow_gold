#ifndef __REC_WIDGET_PANES__
#define __REC_WIDGET_PANES__

#include "rec/base/base.h"
#include "rec/widget/Widget.h"
#include "rec/widget/Panes.pb.h"

namespace rec {
namespace widget {

typedef WidgetBase<juce::TabbedComponent, pane::Navigation> NavigationComponentBase;
  
template <>
inline NavigationComponentBase::WidgetBase(const pane::Navigation& n)
  : juce::TabbedComponent(juce::TabbedButtonBar::Orientation(n.orientation())), desc_(n) {
}

namespace pane {

class NavigationComponent : public NavigationComponentBase {
 public:
  NavigationComponent(const Navigation& d) : NavigationComponentBase(d) {}

  virtual void paint(juce::Graphics& g) { TabbedComponent::paint(g); }

  virtual void paint(juce::Graphics& g, const juce::Rectangle<int>& bounds) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(NavigationComponent);
};

}  // namespace pane
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_PANES__
