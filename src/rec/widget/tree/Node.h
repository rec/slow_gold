#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <set>

#include "rec/base/base.h"
#include "rec/gui/icon/Icon.h"
#include "rec/gui/Font.h"
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
        selected_(false),
        font_(gui::getFont(desc_.widget().font())),
        height_(font_.getHeight()),
        ascent_(font_.getAscent()),
        descent_(height_ - ascent_),
        margin_(d.widget().margin()) {
  }

  virtual bool mightContainSubItems() { return isDirectory(); }
  virtual void itemOpennessChanged(bool isNowOpen) {}

  void paint(juce::Graphics& g) const {
    Painter p(desc_.widget(), &g);
    if (icon_)
      icon_->draw(g, 1.0);

    g.drawSingleLineText(name(), margin_, ascent_ + margin_);
  }

  virtual void paintItem(juce::Graphics& g, int, int) {
    paint(g);
  }

  virtual String name() const { return shadow_.file_.getFileName(); }
  virtual juce::Component* createItemComponent();

  const gui::Rectangle bounds() const { return desc_.widget().bounds(); }

  virtual int getItemWidth() const {
    return font_.getStringWidth(name()) + 2 * margin_;
  }
  virtual int getItemHeight() const {
    return ascent_ + descent_ + 2 * margin_;
  }
  bool alreadyVisited() const { return shadow_.shadow_.exists(); }
  const File& file() const { return shadow_.file_; }

  virtual void itemClicked(const juce::MouseEvent&) {
    operator()(file());
  }
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
  const juce::Font font_;
  const short height_, ascent_, descent_, margin_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

class NodeComponent : public juce::Component {
 public:
  NodeComponent(Node* node)
      : Component(node->name()), node_(node), clicked_(false) {
  }

  virtual void paint(juce::Graphics& g) { node_->paint(g); }
  virtual void mouseDown(const juce::MouseEvent& m) {
    clicked_ = true;
  }
  virtual void mouseUp(const juce::MouseEvent& m) {
    if (clicked_) {
      node_->itemClicked(m);
      clicked_ = false;
    }
  }

 private:
  Node* node_;
  bool clicked_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(NodeComponent);
};

inline juce::Component* Node::createItemComponent() {
  return new NodeComponent(this);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
