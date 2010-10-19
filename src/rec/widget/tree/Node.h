#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <vector>

#include "rec/base/base.h"
#include "rec/gui/icon/Icon.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem {
 public:
  Node(const NodeDesc& d, const Path& path)
      : desc_(d),
        path_(path),
        name_(path.field().end()[-1]),
        ready_(false),
        visited_(false),
        containsMusic_(false),
        icon_(gui::icon::getIcon(desc.icon())) {
  }

  void setName(const string& n) { name_ = n; }
  void setVisited(bool v) { visited_ = v; }

  virtual bool mightContainSubItems() { return false; }
  virtual void itemOpennessChanged(bool isNowOpen) {
    if (isNowOpen && !ready_) {
      fillSubItems();
      ready_ = true;
    }
  }

  const juce::Rectangle& bounds() const { return desc_.widget().bounds(); }

  virtual int getItemWidth() const { return bounds().x(); }
  virtual int getItemHeight() const { return bounds().y(); }
  bool alreadyVisited() const { return visited_; }
  bool containsMusic() const { return containsMusic_; }

  virtual const string& getName() const { return name_; }

  virtual void paintItem(Graphics& g, int width, int height) {
    Paintable p(desc_.widget(), &g);
    if (icon_)
      icon_->draw(g, 1.0);
    g.drawSingleLineText(getName().c_str(), 0, 20);  // TODO
  }
  virtual void fillSubItems() {}

 protected:
  NodeDesc desc_;
  Path path_;
  string name_;
  bool ready_;
  bool visited_;
  bool containsMusic_;
  const juce::Drawable* icon_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
