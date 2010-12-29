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
#include "rec/util/file/VolumeFile.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node : public juce::TreeViewItem,
             public Broadcaster<const VolumeFile&> {
 public:
  Node(const NodeDesc& d, const VolumeFile& vf, const char* name = NULL);

  virtual void requestPartition() {}

  virtual bool mightContainSubItems() { return isDirectory(); }
  virtual const String getUniqueName() { return name(); }
  virtual int getItemWidth() const;
  virtual int getItemHeight() const;
  virtual juce::Component* createItemComponent();
  virtual void itemClicked(const juce::MouseEvent&);
  virtual bool isDirectory() const { return false; }

  const String name() const;
  virtual const String computeName() const;

  void paint(juce::Graphics& g) const;

  const NodeDesc& desc() const { return desc_; }

  const gui::Rectangle bounds() const;

  bool alreadyVisited() const;

  const VolumeFile& volumeFile() const { return volumeFile_; }
  file::Volume::Type type() const { return volumeFile_.volume().type(); }
  bool processing() const { return processing_; }

  void setProcessing(bool p) {
    processing_ = p;
    thread::callAsync(this, &TreeViewItem::repaintItem);
  }

 protected:
  mutable String name_;
  const NodeDesc desc_;
  const VolumeFile volumeFile_;
  Listeners listeners_;
  const juce::Drawable* icon_;
  const juce::Font font_;

 private:
  bool processing_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Node);
  JUCE_LEAK_DETECTOR(Node);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_NODE__
