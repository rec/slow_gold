#ifndef __REC_WIDGET_PANES__
#define __REC_WIDGET_PANES__

#include "rec/base/base.h"
#include "rec/widget/Widget.h"
#include "rec/widget/Panes.pb.h"

namespace rec {
namespace widget {

#if 0
typedef WidgetBase<, pane::Navigation> NavigationComponentBase;
namespace pane {

class NavigationComponent : public NavigationComponentBase,
                            public juce::FileBrowserListener {
 public:
  NavigationComponent(const Navigation& d);

  virtual void paint(juce::Graphics& g) { TabbedComponent::paint(g); }
  virtual void paint(juce::Graphics& g, const juce::Rectangle<int>& bounds) {}

  virtual void selectionChanged() {}
  virtual void fileClicked (const File& file, const juce::MouseEvent& e);
  virtual void fileDoubleClicked (const File& file) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(NavigationComponent);
};

}  // namespace pane
#endif
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_PANES__
