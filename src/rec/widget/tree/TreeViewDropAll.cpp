#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/gui/component/Focusable.h"
#include "rec/data/yaml/Yaml.h"

namespace rec {
namespace widget {
namespace tree {

TreeViewDropAll::TreeViewDropAll(ApplicationCommandManager* m)
    : FocusableTarget(m) {
  setName("Tree");
}

void TreeViewDropAll::paint(Graphics& g) {
  TreeView::paint(g);

  g.setFont(14.0f);

  static const int HEIGHT = 10;
  g.drawFittedText("This is your bookmarks area!  Drop directories and ",
                   0, 0, getWidth(), getHeight() - HEIGHT,
                   juce::Justification::centred, 0);

  g.drawFittedText("files here or double-click for a dialog.",
                   0, HEIGHT, getWidth(), getHeight(),
                   juce::Justification::centred, 0);
  paintFocus(g);
}

bool TreeViewDropAll::isInterestedInFileDrag(const StringArray& files) {
  for (int i = 0; i < files.size(); ++i) {
    if (file::isAudio(files[i]) || File(files[i]).isDirectory())
      return true;
  }
  return false;
}

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
      LOG(ERROR) << "Non Node in TreeViewDropAll";
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
  persist::setGlobal(getSelected(getRootItem(), false));
}

bool TreeViewDropAll::paste(const string& s) {
  VirtualFileList files;
  bool read = yaml::read(s, &files);
  if (read) {
    files.MergeFrom(persist::get<VirtualFileList>());
    persist::setGlobal(files);
  }
  return read;
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
