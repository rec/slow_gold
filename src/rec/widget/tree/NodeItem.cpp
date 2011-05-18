#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/NodeComponent.h"

namespace rec {
namespace widget {
namespace tree {

Node::Node(const NodeDesc& d, const VirtualFile& vf, const char* name)
    : desc_(d),
      volumeFile_(vf),
      icon_(gui::icon::getIcon(d.icon())),
      font_(gui::getFont(desc_.widget().font())),
      topSelection_(false),
      topLevel_(false),
      processing_(false),
      clicked_(false) {
  if (name)
    name_ = name;
}

void Node::paint(juce::Graphics& g) const {
  ScopedLock l(lock_);
  Painter p(desc_.widget(), &g);
  if (icon_)
    icon_->draw(g, 1.0);

  if (isSelected()) {
    g.setColour(juce::Colours::black);
  } else {
    p.setColor(clicked_ ? Painter::BORDER :
               processing_ ? Painter::FOREGROUND : Painter::HIGHLIGHT);
  }
  g.drawSingleLineText(name(), desc_.widget().margin(),
                       static_cast<int>(font_.getAscent() + desc_.widget().margin()));
}

const String Node::name() const {
  if (!name_.length())
    name_ = computeName();

  return name_;
}

void Node::itemClicked(const MouseEvent& e) {
  if (juce::ModifierKeys::getCurrentModifiers().isAnyMouseButtonDown()) {
    if (!isDirectory()) {
      clicked_ = true;
      broadcast(volumeFile_);
    }

    if (!(getParentItem() && getParentItem()->getParentItem())) {
      bool selected = !isSelected();
      setSelected(selected, selected && !e.mods.isShiftDown());
    }
  } else {
    clicked_ = false;
  }
  repaintItem();
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

juce::Component* Node::createItemComponent() {
  return new NodeComponent(this);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
