#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <set>

#include "rec/base/base.h"
#include "rec/gui/Font.h"
#include "rec/gui/icon/Icon.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/util/file/VirtualFile.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem,
             public Broadcaster<const VirtualFile&> {
 public:
  Node(const NodeDesc& d, const VirtualFile& vf, const char* name = NULL);

  virtual void requestPartition() {}

  virtual bool mightContainSubItems() { return isDirectory(); }
  virtual const String getUniqueName() const { return name(); }
  virtual int getItemWidth() const;
  virtual int getItemHeight() const;
  virtual juce::Component* createItemComponent();
  virtual void itemClicked(const MouseEvent& e);
  virtual bool isDirectory() const { return false; }

  const String name() const;
  virtual const String computeName() const;

  void paint(juce::Graphics& g) const;

  const NodeDesc& desc() const { return desc_; }

  const gui::Rectangle bounds() const;

  bool alreadyVisited() const;

  const VirtualFile& volumeFile() const { return volumeFile_; }
  VirtualFile::Type type() const { return volumeFile_.type(); }
  virtual void computeChildren() {}
  bool topSelection() const { return topSelection_ && topLevel_; }
  void setTopLevel(bool lev = true) { topLevel_ = lev; }

 protected:
  void setProcessing(bool p) {
    processing_ = p;
    thread::callAsync(this, &TreeViewItem::repaintItem);
  }

  mutable String name_;
  const NodeDesc desc_;
  const VirtualFile volumeFile_;
  ListenerSet listeners_;
  const juce::Drawable* icon_;
  const juce::Font font_;
  bool topSelection_;
  bool topLevel_;

 private:
  bool processing_;
  bool clicked_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
  JUCE_LEAK_DETECTOR(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
