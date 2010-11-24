#include "rec/widget/tree/Root.h"

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

Root::Root(const NodeDesc& desc) : desc_(desc), root_(new TreeViewItem) {}

Root::~Root() {
  delete getRootItem();
}

void Root::addChildren() {
  setRootItem(root_.get());
  setRootItemVisible(false);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
