#ifndef __REC_WIDGET_TREE_NODE__
#define __REC_WIDGET_TREE_NODE__

#include <set>

#include "rec/gui/Font.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem,
             public Broadcaster<const VirtualFile&> {
 public:
  Node(const NodeDesc& d, const VirtualFile& vf, const char* name = NULL);

  virtual void requestChildren() {}

  virtual bool mightContainSubItems() { return isDirectory(); }
  virtual String getUniqueName() const { return name(); }
  virtual int getItemWidth() const;
  virtual int getItemHeight() const;
  virtual juce::Component* createItemComponent();
  virtual void itemClicked(const MouseEvent& e);
  virtual bool isDirectory() const { return false; }
  void refreshNode(const VirtualFile&);

  const String name() const;
  virtual String computeName() const;

  void paint(juce::Graphics& g) const;

  const NodeDesc& desc() const { return desc_; }

  const gui::Rectangle bounds() const;

  const VirtualFile& file() const { return virtualFile_; }
  const VirtualFile& virtualFile() const { return virtualFile_; }  // TODO
  VirtualFile::Type type() const { return virtualFile_.type(); }
  virtual void computeChildren() {}
  bool topSelection() const { return topSelection_ && topLevel_; }
  void setTopLevel(bool lev = true) { topLevel_ = lev; }

 protected:
  File getVisitedFile() const;

  void setProcessing(bool p) {
    processing_ = p;
    MessageManagerLock l;
    repaintItem();
  }

  mutable String name_;
  const NodeDesc desc_;
  const VirtualFile virtualFile_;
  ListenerSet listeners_;
  const juce::Drawable* icon_;
  const juce::Font font_;
  bool topSelection_;
  bool topLevel_;

 private:
  bool processing_;
  bool clicked_;

  bool isCurrent() const;

  ColorName getColor() const;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
