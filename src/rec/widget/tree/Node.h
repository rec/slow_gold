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

struct ShadowFile {
  File file_;
  File shadow_;

  ShadowFile() {}
  ShadowFile(const File& f, const File& s) : file_(f), shadow_(s) {}
};

class Node : public juce::TreeViewItem {
 public:
  Node(const NodeDesc& d, const ShadowFile& s)
      : desc_(d),
        shadow_(s),
        ready_(false),
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
  bool alreadyVisited() const { return shadow_.shadow_.exists(); }
  bool containsMusic() const { return false; }

  const ShadowFile& shadow() const { return shadow_; }

  virtual String name() const { return shadow_.file_.getFileName(); }

  virtual void paintItem(juce::Graphics& g, int width, int height) {
    Painter p(desc_.widget(), &g);
    if (icon_)
      icon_->draw(g, 1.0);
    g.drawSingleLineText(name(), 0, 20);  // TODO
  }

 protected:
  NodeDesc desc_;
  ShadowFile shadow_;

  bool ready_;
  bool containsMusic_;
  const juce::Drawable* icon_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
