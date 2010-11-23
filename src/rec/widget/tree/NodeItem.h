#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <set>

#include "rec/base/base.h"
#include "rec/gui/Font.h"
#include "rec/gui/icon/Icon.h"
#include "rec/util/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/widget/tree/ShadowFile.h"
#include "rec/widget/tree/Tree.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem,
             public util::Listener<const File&>::Set {
 public:
  Node(const NodeDesc& d, const ShadowFile& s);
  virtual bool mightContainSubItems() { return isDirectory(); }

  void paint(juce::Graphics& g) const;

  virtual void paintItem(juce::Graphics& g, int, int) {
    paint(g);
  }

  const NodeDesc& desc() const { return desc_; }

  virtual String name() const;
  virtual juce::Component* createItemComponent();

  const gui::Rectangle bounds() const;

  virtual int getItemWidth() const;
  virtual int getItemHeight() const;
  bool alreadyVisited() const;
  const File& file() const;

  virtual void itemClicked(const juce::MouseEvent&);
  virtual void requestPartition() {}
  virtual bool isDirectory() const { return false; }

 protected:
  NodeDesc desc_;
  ShadowFile shadow_;
  Listeners listeners_;
  const juce::Drawable* icon_;
  const juce::Font font_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
