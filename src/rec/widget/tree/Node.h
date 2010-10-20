#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <vector>

#include "rec/base/base.h"
#include "rec/gui/icon/Icon.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/widget/Painter.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem {
 public:
  Node(const NodeDesc& d, const File& file, const File& shadow)
      : desc_(d),
        file_(file),
        shadow_(shadow),
        ready_(false),
        containsMusic_(false),
        icon_(gui::icon::getIcon(d.icon())) {
  }

  virtual bool mightContainSubItems() { return false; }
  virtual void itemOpennessChanged(bool isNowOpen) {
    if (isNowOpen && !ready_) {
      fillSubItems();
      ready_ = true;
    }
  }
  virtual void fillSubItems() {}

  const gui::Rectangle bounds() const { return desc_.widget().bounds(); }

  virtual int getItemWidth() const { return bounds().top_left().x(); }
  virtual int getItemHeight() const { return bounds().top_left().y(); }
  bool alreadyVisited() const { return shadow_.exists(); }
  bool containsMusic() const { return containsMusic_; }

  const File& file() const { return file_; }
  const File& shadow() const { return shadow_; }

  virtual void paintItem(juce::Graphics& g, int width, int height) {
    Painter p(desc_.widget(), &g);
    if (icon_)
      icon_->draw(g, 1.0);
    g.drawSingleLineText(file_.getFileName(), 0, 20);  // TODO
  }

 protected:
  NodeDesc desc_;
  File file_;
  File shadow_;

  bool ready_;
  bool containsMusic_;
  const juce::Drawable* icon_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
