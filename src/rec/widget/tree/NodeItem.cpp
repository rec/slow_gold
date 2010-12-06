#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/NodeComponent.h"

namespace rec {
namespace widget {
namespace tree {

Node::Node(const NodeDesc& d, const VolumeFile& vf, const char* name)
    : desc_(d),
      volumeFile_(vf),
      icon_(gui::icon::getIcon(d.icon())),
      font_(gui::getFont(desc_.widget().font())) {
  if (name)
    name_ = name;
}

void Node::paint(juce::Graphics& g) const {
  Painter p(desc_.widget(), &g);
  if (icon_)
    icon_->draw(g, 1.0);

  g.drawSingleLineText(name(), desc_.widget().margin(),
                       font_.getAscent() + desc_.widget().margin());
}

String Node::name() const {
  if (name_.length())
    return name_.c_str();

  Volume::Type type = volumeFile_.volume().type();
  if (int size = volumeFile_.path_size())
    return volumeFile_.path(size - 1).c_str();

  if (type == Volume::MUSIC)
    return "<Music>";

  if (type == Volume::USER)
    return "<User>";

  if (type == Volume::VOLUME || type == Volume::CD) {
    string name = volumeFile_.volume().name();
    eraseVolumePrefix(&name, false);
    return name.empty() ? "<Root>" : name.c_str();
  }

  return "<Unknown>";
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
  return getShadowFile(volumeFile_).exists();
}

File Node::file() const { return getFile(volumeFile_); }

void Node::itemClicked(const juce::MouseEvent&) { 
  operator()(volumeFile_); 
}

juce::Component* Node::createItemComponent() {
  return new NodeComponent(this);
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
