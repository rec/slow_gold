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
  delete getRootItem();
}

void Root::update() {
  VolumeList list = getVolumes();
  setRootItem(&root_);
  setRootItemVisible(false);

  addVolume(Volume::MUSIC, "");
  addVolume(Volume::USER, "");

  VolumeFile vf;
  vf.mutable_volume()->set_type(Volume::VOLUME);
  juce::Array<File> roots;

#if JUCE_MAC
  addVolume(Volume::VOLUME, "");
  File("/Volumes").findChildFiles(roots, File::findFilesAndDirectories, false);
#else
  File::findFileSystemRoots(roots);
#endif

  for (int i = 0; i < roots.size(); ++i) {
    if (roots[i].isOnHardDisk() && roots[i].getLinkedTarget() == roots[i]) {
      string s(roots[i].getFullPathName().toCString());
      addVolume(Volume::VOLUME, s);
    }
  }
}

void Root::addVolume(const VolumeFile& volumeFile) {
  Directory* directory = new Directory(desc_, volumeFile);
  directory->requestPartition();
  directory->listeners()->insert(this);
  root_.addSubItem(directory);
}

void Root::addVolume(Volume::Type type, const string& name) {
  VolumeFile vf;
  vf.mutable_volume()->set_type(type);
  vf.mutable_volume()->set_name(name);
  addVolume(vf);
}

void Root::addVolume(const Volume& volume, int insertAt) {
  VolumeFile vf;
  vf.mutable_volume()->CopyFrom(volume);

  Directory* directory = new Directory(desc_, vf);
  directory->listeners()->insert(this);
  root_.addSubItem(directory, insertAt);
  directory->requestPartition();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
