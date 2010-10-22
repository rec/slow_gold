#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <vector>

#include "rec/base/base.h"
#include "rec/gui/icon/Icon.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/widget/tree/Tree.h"
#include "rec/widget/Painter.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem {
 public:
  Node(const NodeDesc& d, const ShadowFile& s);

  virtual bool mightContainSubItems() { return false; }
  virtual void itemOpennessChanged(bool isNowOpen) {}
  virtual void paintItem(juce::Graphics& g, int width, int height);

  virtual String name() const { return shadow_.file_.getFileName(); }

  const gui::Rectangle bounds() const { return desc_.widget().bounds(); }

  virtual int getItemWidth() const { return bounds().top_left().x(); }
  virtual int getItemHeight() const { return bounds().top_left().y(); }
  bool alreadyVisited() const { return shadow_.shadow_.exists(); }

 protected:
  NodeDesc desc_;
  ShadowFile shadow_;

  const juce::Drawable* icon_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
