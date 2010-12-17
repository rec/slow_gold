#include <glog/logging.h>

#include "rec/widget/tree/Root.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/WaitLoop.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/GetVolumes.h"

using namespace juce;
using namespace rec::thread;

namespace rec {
namespace widget {
namespace tree {

using namespace rec::gui;

static const int ROOT_WAIT_TIME = 1000;

Root::Root(const NodeDesc& desc) : Thread("tree::Root"), desc_(desc) {
  const Colors& colors = desc_.widget().colors();
  tree_.setColour(juce::TreeView::backgroundColourId, color::get(colors, 1));
}

void Root::run() {
  while (!threadShouldExit()) {
    volumes_ = getVolumes();
    triggerAsyncUpdate();
    wait(ROOT_WAIT_TIME);
  }
}

void Root::handleAsyncUpdate() {
  for (int i = 0, j = 0; i < volumes_.size() || j < getNumNodes(); ++i) {
    const Volume* v1 = (i < volumes_.size()) ? &volumes_[i] : NULL;
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

  tree_.setRootItem(&root_);
  tree_.setRootItemVisible(false);
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
