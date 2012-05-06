#include "rec/slow/GuiSettings.h"

#include "rec/slow/GuiSettings.pb.h"
#include "rec/data/DataOps.h"

namespace rec {
namespace slow {

using namespace juce;

namespace {

File browseForFileToSaveNoTreeView(const String& msg, const File& startFile) {
  FileChooser c(msg, startFile);
  return c.browseForFileToSave(true) ? c.getResult() : File::nonexistent;
}

File browseForFileToSaveTreeView(const String& msg, const File& startFile) {
  int flags = FileBrowserComponent::saveMode +
    FileBrowserComponent::canSelectFiles +
    FileBrowserComponent::useTreeView;

  FileBrowserComponent fileBrowser(flags, startFile, NULL, NULL);
  FileChooserDialogBox dialogBox(msg, "", fileBrowser, true, Colours::white);
  return dialogBox.show() ? fileBrowser.getSelectedFile(0) : File::nonexistent;
}

}

File browseForFileToSave(const String& msg, const File& startFile) {
  GuiSettings settings = data::getGlobal<GuiSettings>();
  return settings.use_tree_view_in_file_dialogs() ?
    browseForFileToSaveTreeView(msg, startFile) : browseForFileToSave(msg, startFile);
}

}  // namespace slow
}  // namespace rec
