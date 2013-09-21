#include "rec/util/file/CurrentFileBase.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/menu/RecentFiles.h"
#include "rec/program/JuceModel.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

void CurrentFileBase::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (files.file_size() >= 1)
    setVirtualFile(files.file(0), true);
}

void CurrentFileBase::setFile(const File& f, bool showError) {
  setVirtualFile(file::toVirtualFile(f), showError);
}

void CurrentFileBase::operator()(const VirtualFile& vf) {
  setVirtualFile(vf, true);
}

void CurrentFileBase::setVirtualFile(const VirtualFile& f, bool showError) {
  data::getDataCenter()->waitTillClear();
  data::getDataCenter()->clearUndoes();

  suspend();

  if (file_.path_size())
    gui::addRecentFile(file_, *getFileDescription());

  VirtualFile newFile = f;
  file_.Swap(&newFile);

  beforeFileChange();

  empty_ = determineIfFileEmpty(showError);
  if (empty_)
    file_ = data::noData();
  else
    nonEmptyFileLoaded();

  afterFileChange(newFile);
  data::setProto(file_, CANT_UNDO);
  data::UntypedDataListener::setGlobalDataFile(file_);

  resume();
  program::menuItemsChanged();
}

}  // namespace file
}  // namespace util
}  // namespace rec
