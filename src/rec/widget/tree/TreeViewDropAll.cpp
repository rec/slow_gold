#include "rec/widget/tree/TreeViewDropAll.h"

namespace rec {
namespace widget {
namespace tree {

TreeViewDropAll::TreeViewDropAll() : TreeViewDrop("Tree") {
  dropBroadcaster()->addListener(this);
}

void TreeViewDropAll::operator()(const VolumeFile& f) {
  persist::data<file::VolumeFileList>()->append("file", f);
}

void TreeViewDropAll::paint(Graphics& g) {
  TreeView::paint(g);

 g.setFont(14.0f);
  static const int HEIGHT = 10;
  g.drawFittedText("Drop directories and files here, or",
                   0, 0, getWidth(), getHeight() - HEIGHT,
                   juce::Justification::centred, 0);

  g.drawFittedText("click to add directories and files.",
                   0, HEIGHT, getWidth(), getHeight(),
                   juce::Justification::centred, 0);
}

bool TreeViewDropAll::isInterestedInFileDrag(const StringArray& files) {
  for (int i = 0; i < files.size(); ++i) {
    if (file::isAudio(files[i]) || File(files[i]).isDirectory())
      return true;
  }
  return false;
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
