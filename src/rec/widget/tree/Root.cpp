#include "rec/widget/tree/Root.h"
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/GetVolumes.h"
#include "rec/gui/Color.h"

#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {

using namespace rec::gui;

Root::Root(const NodeDesc& desc) : desc_(desc) {
  const Colors& colors = desc_.widget().colors();
  setColour(juce::TreeView::backgroundColourId, color::get(colors, 1));
}

Root::~Root() {
}

void Root::update() {
  VolumeList volumes = getVolumes();

  for (int i = 0, j = 0; i < volumes.size() || j < getNumNodes(); ++i) {
    const Volume* v1 = (i < volumes.size()) ? &volumes[i] : NULL;
    const Node* n = (j < getNumNodes()) ? getNode(j) : NULL;
    const Volume* v2 = n ? &(n->volumeFile().volume()) : NULL;

    if (!v1)
      root_.removeSubItem(j);
    else if (!v2 || compareVolumes(*v1, *v2))
      addVolume(*v1, j++);
    else if (compareVolumes(*v2, *v1))
      root_.removeSubItem(j);
    else  // They're the same!
      j++;
  }
  setRootItem(&root_);
  setRootItemVisible(false);
}

void Root::addVolume(const Volume& volume, int insertAt) {
  VolumeFile vf;
  vf.mutable_volume()->CopyFrom(volume);

  Directory* directory = new Directory(desc_, vf);
  directory->addListener(this);
  root_.addSubItem(directory, insertAt);
  directory->requestPartition();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
