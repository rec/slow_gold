#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <set>

#include "rec/base/base.h"
#include "rec/gui/icon/Icon.h"
#include "rec/util/Listener.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/widget/tree/Tree.h"
#include "rec/widget/Painter.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem,
             public util::Listener<const File&>::Set {
 public:
  Node(const NodeDesc& d, const ShadowFile& s)
      : desc_(d),
        shadow_(s),
        icon_(gui::icon::getIcon(d.icon())),
        selected_(false) {
  }

  virtual bool mightContainSubItems() { return isDirectory(); }
  virtual void itemOpennessChanged(bool isNowOpen) {}
  void paint(juce::Graphics& g) const {
    Painter p(desc_.widget(), &g);
    if (icon_)
      icon_->draw(g, 1.0);
    g.drawSingleLineText(name(), 0, 20);  // TODO
  }

  virtual String name() const { return shadow_.file_.getFileName(); }
  virtual juce::Component* createItemComponent();

  const gui::Rectangle bounds() const { return desc_.widget().bounds(); }

  virtual int getItemWidth() const { return 200; }  // bounds().top_left().x(); }
  virtual int getItemHeight() const { return 25; } // bounds().top_left().y(); }
  bool alreadyVisited() const { return shadow_.shadow_.exists(); }
  const File& file() const { return shadow_.file_; }

  virtual void itemClicked(const juce::MouseEvent&) { operator()(file()); }
  virtual void itemDoubleClicked(const juce::MouseEvent& m) { itemClicked(m); }
  virtual void requestPartition() {}
  virtual bool isDirectory() const { return false; }
  virtual void itemSelectionChanged(bool s) {
    selected_ = s;
    TreeViewItem::itemSelectionChanged(s);
  }

 protected:
  NodeDesc desc_;
  ShadowFile shadow_;
  Listeners listeners_;
  const juce::Drawable* icon_;
  bool selected_;
               
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

class NodeComponent : public juce::Component {
 public:
  NodeComponent(const String& name, const Node& node)
      : Component(name), node_(node) {
  }

  virtual void paint(juce::Graphics& g) { node_.paint(g); }

 private:
  const Node& node_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(NodeComponent);
};

inline juce::Component* Node::createItemComponent() {
  return new NodeComponent(this->name(), *this);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
