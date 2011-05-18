#ifndef __REC_WIDGET_TREE_NODECOMPONENT__
#define __REC_WIDGET_TREE_NODECOMPONENT__

#include "rec/widget/tree/NodeItem.h"

namespace rec {
namespace widget {
namespace tree {

class NodeComponent : public juce::Component {
 public:
  NodeComponent(Node* n) : Component(n->name()), node_(n) {}
  virtual void paint(juce::Graphics& g)           { node_->paint(g); }
  virtual void mouseDown(const juce::MouseEvent& e) { node_->itemClicked(e); }
  virtual void mouseUp(const juce::MouseEvent& e)   { node_->itemClicked(e); }
#if 0
    if (!node_->isDirectory())
      node_->setSelected(true, true);

    node_->itemClicked(e);
  }

  virtual void mouseUp(const juce::MouseEvent& e)   {
    if (!node_->isDirectory())
      node_->setSelected(false, true);
  }
#endif

 private:
  Node* node_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(NodeComponent);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODECOMPONENT__
