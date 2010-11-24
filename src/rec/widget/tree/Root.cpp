#include "rec/widget/tree/Root.h"
#include "rec/widget/tree/Directory.h"
#include "rec/gui/Color.h"

#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {

namespace {

class TreeViewItem : public juce::TreeViewItem {
 public:
  bool mightContainSubItems() { return true; }
};

}  // namespace

using namespace rec::gui;

Root::Root(const NodeDesc& desc) : desc_(desc), root_(new TreeViewItem) {
  const Colors& colors = desc_.widget().colors();
  setColour(juce::TreeView::backgroundColourId, color::get(colors, 1));
}

Root::~Root() {
  delete getRootItem();
}

void Root::addChildren() {
  setRootItem(root_.get());
  setRootItemVisible(false);
  addVolume(Volume::MUSIC);
  addVolume(Volume::USER);
}

void Root::addFile(const VolumeFile& volumeFile) {
  Directory* directory = new Directory(desc_, volumeFile);
  directory->requestPartition();
  directory->listeners()->insert(this);
  root_->addSubItem(directory);
}

void Root::addVolume(Volume::Type type) {
  VolumeFile vf;
  vf.mutable_volume()->set_type(type);
  addFile(vf);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
