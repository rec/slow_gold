#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <vector>

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public WidgetBase<NodeDesc>, public juce::TreeViewItem {
 public:
  Node(const Widget& widget, const string& name)
      : widget_(widget),
        name_(name),
        ready_(false) {
  }

  virtual bool mightContainSubItems() = 0;
  virtual void itemOpennessChanged(bool isNowOpen) {
    if (isNowOpen && !ready_) {
      fillSubItems();
      ready_ = true;
    }
  }

  const gui::Rectangle& bounds() const { return desc_.widget().bounds(); }

  virtual int getItemWidth() const { return bounds().x(); }
  virtual int getItemHeight() const { return bounds().y(); }
  virtual const Drawable* getIcon() const { return NULL; }

  virtual string getName() const { return name; }

  virtual void paintItem(Graphics& g, int width, int height) {
    if (const Drawable* icon = getIcon())
      icon->draw(g, 1.0);
    g.drawSingleLineText(getName().c_str(), 0, 0);
  }
  virtual void fillSubItems() = 0;

 private:
  Widget widget_;
  string name_;
  bool ready_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
