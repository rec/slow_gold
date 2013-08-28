#include "rec/slow/GuiSettings.h"

#include "rec/slow/GuiSettings.pb.h"
#include "rec/data/DataOps.h"

namespace rec {
namespace slow {

using namespace juce;

namespace {

File browseForFileNoTreeView(const String& msg, const File& startFile,
                             SaveOrOpen save, const String& filter) {
  FileChooser c(msg, startFile, filter);
  bool success = (save == SAVE_FILE) ? c.browseForFileToSave(true) :
    c.browseForFileToOpen();
  return success ? c.getResult() : File::nonexistent;
}

File browseForFileTreeView(const String& msg, const File& startFile,
                           SaveOrOpen save, const String& filter) {
  int flags = (save == SAVE_FILE ? FileBrowserComponent::saveMode :
               FileBrowserComponent::openMode) +
    FileBrowserComponent::canSelectFiles +
    FileBrowserComponent::useTreeView;

  WildcardFileFilter wildFilter(filter, "", "");

  FileBrowserComponent fileBrowser(flags, startFile, &wildFilter, nullptr);
  FileChooserDialogBox dialogBox(msg, "", fileBrowser, true, Colours::white);
  return dialogBox.show() ? fileBrowser.getSelectedFile(0) : File::nonexistent;
}

}

File browseForFile(const String& msg, const File& startFile, SaveOrOpen save,
                   const String& filter) {
  GuiSettings settings = data::getProto<GuiSettings>();
  File f = settings.use_tree_view_in_file_dialogs() ?
    browseForFileTreeView(msg, startFile, save, filter) :
    browseForFileNoTreeView(msg, startFile, save, filter);

  return File(File::createLegalPathName(f.getFullPathName()));
}

}  // namespace slow
}  // namespace rec
