#include "rec/widget/tree/Root.h"

#include "rec/data/Data.h"
#include "rec/gui/Color.h"
#include "rec/app/Files.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/CD.h"
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/NavigatorConfig.pb.h"

using namespace juce;
using namespace rec::thread;
using namespace rec::util::file;

namespace rec {
namespace widget {
namespace tree {

using namespace rec::gui;

static const int ROOT_WAIT_TIME = 1000;

static File getOpennessFile() {
  return app::getAppFile("TreeOpenness.xml");
}

Root::Root(MenuBarModel* model, const NodeDesc& desc)
  : desc_(desc),
    tree_(model),
    addDialogOpen_(false),
    opennessRead_(false),
    opennessStarted_(false) {
  const Colors& colors = desc_.widget().colors();
  tree_.setColour(juce::TreeView::backgroundColourId, color::get(colors, 1));
  tree_.addMouseListener(this, false);
  tree_.setRootItem(&root_);
  tree_.setRootItemVisible(false);

  data::TypedEditable<VirtualFileList>* setter =
    data::editable<VirtualFileList>();
  setter->addListener(this);
  volumes_ = setter->get();
}

void Root::checkVolumes() {
  Lock l(lock_);
  VirtualFileList volumes(volumes_);
  fillVolumes(&volumes);
  thread::callAsync(this, &Root::mergeNewIntoOld, volumes);
}

static void restoreOpenness(Node* node, const XmlElement& xml) {
  node->computeChildren();
  node->setOpen(true);
  forEachXmlChildElement(xml, child) {
    if (child->getTagName() == "OPEN") {
      const String& id = child->getStringAttribute("id");
      int i = 0, n = node->getNumSubItems();
      for (; i < n && node->getSubItem(i)->getUniqueName() != id; ++i);
      if (i < n)
        restoreOpenness(dynamic_cast<Node*>(node->getSubItem(i)), *child);
      else
        LOG(DFATAL) << "Didn't find id " << id;
    }
  }
}

void Root::readOpenness() {
  if (opennessStarted_)
    return;
  opennessStarted_ = true;
  ptr<XmlElement> openness(juce::XmlDocument::parse(getOpennessFile()));
  if (openness) {
    restoreOpenness(&root_, *openness);
    tree_.restoreOpennessState(*openness, true);
  } else {
    LOG(WARNING) << "Couldn't find openness file " << str(getOpennessFile());
  }
  opennessRead_ = true;
}

void Root::writeOpenness() {
  if (opennessRead_) {
    // TODO: only do this when the openness is actually changed!
    ptr<XmlElement> openness(tree_.getOpennessState(true));
    if (!(openness && openness->writeToFile(getOpennessFile(), "")))
      LOG(DFATAL) << "Couldn't write openness file";
  } else {
    readOpenness();
  }
}

void Root::operator()(const VirtualFile& file) {
	broadcast(file);
}

void Root::operator()(const VirtualFileList& volumes) {
  Lock l(lock_);
  volumes_ = volumes;
  // notify();  // TODO!
}

void Root::refreshNode(const VirtualFile& f) {
  root_.refreshNode(f);
}

void Root::mouseDoubleClick(const juce::MouseEvent&) {
  thread::callAsync(this, &Root::doAdd);
}

void Root::doAdd() {
  if (addDialogOpen_ || !data::getGlobal<NavigatorConfig>().allow_file_drop())
    return;

  addDialogOpen_ = true;
  juce::FileChooser chooser("Please choose files or directories to add", File::nonexistent,
                            file::audioFilePatterns(), true);

  if (chooser.browseForMultipleFilesOrDirectories()) {
    StringArray s;
    juce::Array<File> results = chooser.getResults();
    for (int i = 0; i < results.size(); ++i)
      s.add(results[i].getFullPathName());
    tree_.filesDropped(s, 0, 0);
  }
  addDialogOpen_ = false;
}

void Root::mergeNewIntoOld(file::VirtualFileList volumes) {
  for (int i = 0, j = 0; i < volumes.file_size() || j < getNumNodes(); ++i) {
    const VirtualFile* v1 = (i < volumes.file_size()) ? &volumes.file(i) : NULL;
    const Node* n = (j < getNumNodes()) ? getNode(j) : NULL;
    const VirtualFile* v2 = n ? &(n->virtualFile()) : NULL;

    if (!v1)
      root_.removeSubItem(j);
    else if (!v2 || compare(*v1, *v2))
      addVolume(*v1, j++);
    else if (compare(*v2, *v1))
      root_.removeSubItem(j);
    else  // They're the same!
      j++;
  }
  writeOpenness();
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
  directory.transfer()->requestChildren();
}

bool Root::run() {
  return widget::tree::Directory::computeChildrenInBackground();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
