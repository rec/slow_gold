#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/NodeComponent.h"

namespace rec {
namespace widget {
namespace tree {

Node::Node(const NodeDesc& d, const ShadowFile& s)
    : desc_(d),
      shadow_(s),
      icon_(gui::icon::getIcon(d.icon())),
      font_(gui::getFont(desc_.widget().font())),
      height_(font_.getHeight()),
      ascent_(font_.getAscent()),
      descent_(height_ - ascent_),
      margin_(d.widget().margin()) {
}

void Node::paint(juce::Graphics& g) const {
  Painter p(desc_.widget(), &g);
  if (icon_)
    icon_->draw(g, 1.0);

  g.drawSingleLineText(name(), margin_, ascent_ + margin_);
}

String Node::name() const { return shadow_.file_.getFileName(); }

const gui::Rectangle Node::bounds() const { return desc_.widget().bounds(); }

int Node::getItemWidth() const {
  return font_.getStringWidth(name()) + 2 * margin_;
}

int Node::getItemHeight() const {
  return ascent_ + descent_ + 2 * margin_;
}

bool Node::alreadyVisited() const { return shadow_.shadow_.exists(); }
const File& Node::file() const { return shadow_.file_; }

void Node::itemClicked(const juce::MouseEvent&) { operator()(file()); }

juce::Component* Node::createItemComponent() {
  return new NodeComponent(this);
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
