#ifndef __REC_WIDGET_TREE_NODECOMPONENT__
#define __REC_WIDGET_TREE_NODECOMPONENT__

#include "rec/widget/tree/NodeItem.h"

namespace rec {
namespace widget {
namespace tree {

class NodeComponent : public juce::Component {
 public:
  NodeComponent(Node* n) : Component(n->name()), node_(n), clicked_(false) {}

  virtual void paint(juce::Graphics& g) { node_->paint(g); }

  virtual void mouseDown(const juce::MouseEvent& m) { node_->setClicked(true); }

  virtual void mouseUp(const juce::MouseEvent& m) {
    node_->setClicked(false);
  }

 private:
  Node* node_;
  bool clicked_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(NodeComponent);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODECOMPONENT__
