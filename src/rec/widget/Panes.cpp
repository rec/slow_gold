#include "glog/logging.h"
#include "rec/widget/Panes.h"

namespace rec {
namespace widget {
namespace pane {

#if 0
using juce::FileBrowserComponent;

NavigationComponent::NavigationComponent(const Navigation& d)
    : NavigationComponentBase(d) {

  FileBrowserComponent* fileBrowser = new FileBrowserComponent(
      FileBrowserComponent::openMode +
      FileBrowserComponent::canSelectFiles +
      FileBrowserComponent::useTreeView +
      FileBrowserComponent::filenameBoxIsReadOnly,
      File::getSpecialLocation(File::userMusicDirectory),
      NULL, NULL);
  fileBrowser->addListener(this);
  addTab("Disk", colour(0), fileBrowser, true);

  // addTab("CD", colour(0), NULL, true);
  // addTab("URL", colour(0), NULL, true);
}

void NavigationComponent::fileClicked (const File& file,
                                       const juce::MouseEvent& e) {
  LOG(INFO) << "Found file" << file.getFullPathName().toCString();
}

#endif
}  // namespace pane
}  // namespace widget
}  // namespace rec
