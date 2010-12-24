#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <set>

#include "rec/base/base.h"
#include "rec/gui/Font.h"
#include "rec/gui/icon/Icon.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/widget/tree/NodeComponent.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem,
             public listener::Broadcaster<const VolumeFile&> {
 public:
  Node(const NodeDesc& d, const VolumeFile& f, const string& name = string())
      : name_(name),
        desc_(d),
        volumeFile_(vf),
        icon_(gui::icon::getIcon(desc_.icon())),
        font_(gui::getFont(desc_.widget().font())) {{
  }

  const String name() const {
    return (name_.length() ? name_ : getDisplayName(volumeFile_)).c_str();
  }

  const gui::Rectangle bounds() const {
    return desc_.widget().layer().bounds();
  }

  int getItemWidth() const {
    return font_.getStringWidth(name()) + 2 * desc_.widget().margin();
  }

  int getItemHeight() const {
    return font_.getHeight() + 2 * desc_.widget().margin();
  }

  void paint(juce::Graphics& g) const {
    Painter p(desc_.widget(), &g);
    if (icon_)
      icon_->draw(g, 1.0);

    g.drawSingleLineText(name(), desc_.widget().margin(),
                         font_.getAscent() + desc_.widget().margin());
  }

  void itemClicked(const juce::MouseEvent&) { broadcast(volumeFile_); }
  juce::Component* createItemComponent() { return new NodeComponent(this); }
  virtual void requestPartition() {}
  virtual bool mightContainSubItems() { return isDirectory(); }
  virtual const String getUniqueName() { return name(); }
  virtual bool isDirectory() const { return false; }
  const NodeDesc& desc() const { return desc_; }
  const VolumeFile& volumeFile() const { return volumeFile_; }
  Volume::Type type() const { return volumeFile_.volume().type(); }

 protected:
  string name_;
  NodeDesc desc_;
  VolumeFile volumeFile_;
  Listeners listeners_;
  const juce::Drawable* icon_;
  const juce::Font font_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
  JUCE_LEAK_DETECTOR(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
