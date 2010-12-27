#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/NodeComponent.h"

namespace rec {
namespace widget {
namespace tree {

Node::Node(const NodeDesc& d, const VolumeFile& vf, const char* name)
    : desc_(d),
      volumeFile_(vf),
      icon_(gui::icon::getIcon(d.icon())),
      font_(gui::getFont(desc_.widget().font())),
      processing_(false) {
  if (name)
    name_ = name;
}

void Node::paint(juce::Graphics& g) const {
  Painter p(desc_.widget(), &g);
  if (icon_)
    icon_->draw(g, 1.0);
  p.setColor(processing_ ? Painter::FOREGROUND : Painter::HIGHLIGHT);
  g.drawSingleLineText(name(), desc_.widget().margin(),
                       font_.getAscent() + desc_.widget().margin());
}

const String Node::name() const {
  if (!name_.length())
    name_ = computeName();

  return name_;
}

const String Node::computeName() const {
  return getDisplayName(volumeFile_);
}

const gui::Rectangle Node::bounds() const {
  return desc_.widget().layer().bounds();
}

int Node::getItemWidth() const {
  return font_.getStringWidth(name()) + 2 * desc_.widget().margin();
}

int Node::getItemHeight() const {
  return font_.getHeight() + 2 * desc_.widget().margin();
}

bool Node::alreadyVisited() const {
  return getShadowDirectory(volumeFile_).exists();
}

void Node::itemClicked(const juce::MouseEvent&) {
  broadcast(volumeFile_);
}

juce::Component* Node::createItemComponent() {
  return new NodeComponent(this);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
