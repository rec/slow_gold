#include "rec/widget/tree/Root.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/LockedMessage.h"
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

Root::Root(const NodeDesc& desc) : Thread("tree::Root"), desc_(desc) {
  const Colors& colors = desc_.widget().colors();
  setColour(juce::TreeView::backgroundColourId, color::get(colors, 1));
  Runnable* callback = makeCallback(this, &Root::update);
  Runnable* locked = new LockedMessage(callback);
  thread_.reset(new RunnableThread("Polling for volumes", new WaitLoop(1000, locked)));
}

Root::~Root() {
  util::thread::trash::discard(thread_.transfer());
}

bool Root::update() {
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
  return true;
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
