#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/data/DataOps.h"
#include "rec/data/Value.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/gui/component/Focusable.h"
#include "rec/widget/tree/NavigatorConfig.pb.h"
#include "rec/widget/tree/NodeItem.h"

namespace rec {
namespace widget {
namespace tree {

TreeViewDropAll::TreeViewDropAll(MenuBarModel* m)
    : FocusableTarget(m) {
  setName("Tree");
}

bool TreeViewDropAll::isTreeDrop(const Component* c) const {
  return (c == this) && data::getGlobal<NavigatorConfig>().allow_file_drop();
}

void TreeViewDropAll::paint(Graphics& g) {
  TreeView::paint(g);

  g.setFont(14.0f);

  if (isTreeDrop(this)) {
    static const int HEIGHT = 10;
    g.drawFittedText("This is your bookmarks area!  Drop directories and ",
                     0, 0, getWidth(), getHeight() - HEIGHT,
                     juce::Justification::centred, 0);

    g.drawFittedText("files here or double-click for a dialog.",
                     0, HEIGHT, getWidth(), getHeight(),
                     juce::Justification::centred, 0);
  } else if (!getRootItem()->getNumSubItems()) {
#if 0
    juce::Rectangle<float> bounds(0, 0, static_cast<float>(getWidth()),
      static_cast<float>(getHeight()));
    slowGoldIcon_->drawWithin(g, bounds,
                              juce::RectanglePlacement::stretchToFit, 0.4f);
#endif
  }
  paintFocus(g);
}

bool TreeViewDropAll::isInterestedInFileDrag(const StringArray& files) {
  if (!isTreeDrop(this))
    return FocusableTarget::isInterestedInFileDrag(files);

  for (int i = 0; i < files.size(); ++i) {
    if (!file::isAudio(files[i]) || File(files[i]).isDirectory())
      return false;
  }
  return true;
}
#ifdef TREE_VIEW_IS_CUTTABLE

bool TreeViewDropAll::canCopy() const {
  juce::TreeViewItem* root = getRootItem();
  int i = 0;
  for (; i < root->getNumSubItems(); ++i) {
    if (root->getSubItem(i)->isSelected())
      return true;
  }
  return false;
}

static VirtualFileList getSelected(juce::TreeViewItem* root, bool selected) {
  VirtualFileList files;
  for (int i = 0; i < root->getNumSubItems(); ++i) {
    Node* node = dynamic_cast<Node*>(root->getSubItem(i));
    if (!node) {
      LOG(DFATAL) << "Non Node in TreeViewDropAll";
      continue;
    }
    if (node->isSelected() == selected)
      files.add_file()->CopyFrom(node->file());
  }
  return files;
}

string TreeViewDropAll::copy() const {
  return yaml::write(getSelected(getRootItem(), true));
}

void TreeViewDropAll::cut() {
  data::set(getSelected(getRootItem(), false));
}

bool TreeViewDropAll::paste(const string& s) {
  VirtualFileList files;
  bool read = yaml::read(s, &files);
  if (read) {
    files.MergeFrom(data::getGlobal<VirtualFileList>());
    data::set(files);
  }
  return read;
}

#endif

}  // namespace tree
}  // namespace widget
}  // namespace rec
