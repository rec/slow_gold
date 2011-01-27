#include "rec/widget/tree/Root.h"

#include "rec/data/persist/Persist.h"
#include "rec/gui/Color.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/CD.h"
#include "rec/widget/tree/Directory.h"

using namespace juce;
using namespace rec::thread;
using namespace rec::util::file;

namespace rec {
namespace widget {
namespace tree {

using namespace rec::gui;

static const int ROOT_WAIT_TIME = 1000;

Root::Root(const NodeDesc& desc)
    : Thread("tree::Root"), desc_(desc), addDialogOpen_(false) {
  const Colors& colors = desc_.widget().colors();
  tree_.setColour(juce::TreeView::backgroundColourId, color::get(colors, 1));
  persist::data<VirtualFileList>()->addListener(this);
  persist::data<VirtualFileList>()->requestUpdate();
  tree_.addMouseListener(this, false);
}

void Root::run() {
  while (!threadShouldExit()) {
    VirtualFileList volumes;
    {
      ScopedLock l(lock_);
      volumes = volumes_;
    }

    fillVolumes(&volumes);
    if (!threadShouldExit()) {
      thread::callAsync(this, &Root::mergeNewIntoOld, volumes);
      wait(ROOT_WAIT_TIME);
    }
  }
}

void Root::operator()(const VirtualFile& file) {
	broadcast(file);
}

void Root::operator()(const VirtualFileList& volumes) {
  ScopedLock l(lock_);
  volumes_ = volumes;
  notify();
}

void Root::mouseDoubleClick(const juce::MouseEvent&) {
  thread::callAsync(this, &Root::doAdd);
}

void Root::doAdd() {
  if (addDialogOpen_)
    return;
  addDialogOpen_ = true;
  juce::FileChooser chooser("Please choose files or directories to add", File::nonexistent,
                            file::audioFilePatterns(), true);

  if (chooser.browseForMultipleFilesOrDirectories()) {
    const juce::Array<File>& files = chooser.getResults();
    for (int i = 0; i < files.size(); ++i)
      tree_.dropBroadcaster()->broadcast(toVirtualFile(files[i]));
  }
  addDialogOpen_ = false;
}


void Root::mergeNewIntoOld(const file::VirtualFileList& volumes) {
  for (int i = 0, j = 0; i < volumes.file_size() || j < getNumNodes(); ++i) {
    const VirtualFile* v1 = (i < volumes.file_size()) ? &volumes.file(i) : NULL;
    const Node* n = (j < getNumNodes()) ? getNode(j) : NULL;
    const VirtualFile* v2 = n ? &(n->volumeFile()) : NULL;

    if (!v1)
      root_.removeSubItem(j);
    else if (!v2 || compare(*v1, *v2))
      addVolume(*v1, j++);
    else if (compare(*v2, *v1))
      root_.removeSubItem(j);
    else  // They're the same!
      j++;
  }

  tree_.setRootItem(&root_);
  tree_.setRootItemVisible(false);
}

void Root::addVolume(const VirtualFile& volume, int insertAt) {
  ptr<Node> directory;

  if (volume.type() == VirtualFile::CD)
    directory.reset(new CD(desc_, volume));
  else if (getFile(volume).isDirectory())
    directory.reset(new Directory(desc_, volume));
  else
    directory.reset(new Node(desc_, volume));

  directory->addListener(this);
  root_.addSubItem(directory.get(), insertAt);
  directory.transfer()->requestPartition();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
