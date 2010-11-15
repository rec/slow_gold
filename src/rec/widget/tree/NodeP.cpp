#include "rec/widget/tree/Node.h"

namespace rec {
namespace widget {
namespace tree {

Node::Node(const NodeDesc& d, const ShadowFile& s)
    : desc_(d),
      shadow_(s),
      icon_(gui::icon::getIcon(d.icon())) {
}

void Node::paintItem(juce::Graphics& g, int width, int height) {
  Painter p(desc_.widget(), &g);
  if (icon_)
    icon_->draw(g, 1.0);
  g.drawSingleLineText(name(), 0, 20);  // TODO
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
