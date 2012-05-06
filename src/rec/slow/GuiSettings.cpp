#include "rec/slow/GuiSettings.h"

#include "rec/slow/GuiSettings.pb.h"
#include "rec/data/DataOps.h"

namespace rec {
namespace slow {

using namespace juce;

namespace {

File browseForFileNoTreeView(const String& msg, const File& startFile,
                             SaveOrOpen save) {
  FileChooser c(msg, startFile);
  bool success = (save == SAVE_FILE) ? c.browseForFileToSave(true) :
    c.browseForFileToOpen();
  return success ? c.getResult() : File::nonexistent;
}

File browseForFileTreeView(const String& msg, const File& startFile,
                           SaveOrOpen save) {
  int flags = (save == SAVE_FILE ? FileBrowserComponent::saveMode :
               FileBrowserComponent::openMode) +
    FileBrowserComponent::canSelectFiles +
    FileBrowserComponent::useTreeView;

  FileBrowserComponent fileBrowser(flags, startFile, NULL, NULL);
  FileChooserDialogBox dialogBox(msg, "", fileBrowser, true, Colours::white);
  return dialogBox.show() ? fileBrowser.getSelectedFile(0) : File::nonexistent;
}

}

File browseForFile(const String& msg, const File& startFile, SaveOrOpen save) {
  GuiSettings settings = data::getGlobal<GuiSettings>();
  return settings.use_tree_view_in_file_dialogs() ?
    browseForFileTreeView(msg, startFile, save) :
    browseForFileNoTreeView(msg, startFile, save);
}

}  // namespace slow
}  // namespace rec
