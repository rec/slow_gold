#include "rec/slow/CurrentFile.h"

#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/command/Command.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/RecentFiles.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::data;

namespace {

Trans RAN_OUT_OF_MEMORY("Ran Out Of Memory For Your File");
Trans RAN_OUT_OF_MEMORY_FULL("Your file was so large that the program "
                             "ran out of memory.");
}

using namespace rec::widget::waveform;
using namespace juce;

CurrentFile::CurrentFile(Instance* i) : HasInstance(i) {
}

CurrentFile::~CurrentFile() {}

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (files.file_size() >= 1)
    setDataFile(&files.file(0));
}

void CurrentFile::setFile(const File& f) {
  setVirtualFile(file::toVirtualFile(f));
}

void CurrentFile::operator()(const VirtualFile& vf) {
  setDataFile(&vf);
}

const SampleTime CurrentFile::length() const {
  Lock l(lock_);
  return length_;
}

void CurrentFile::setVirtualFile(const VirtualFile& vf) {
  setDataFile(&vf);
}

void CurrentFile::setDataFile(DataFile f, bool showError) {
  data::getDataCenter().waitTillClear();
  data::getDataCenter().clearUndoes();

  player()->reset();
  instance_->reset();
  currentTime()->reset();

  if (file_)
    gui::addRecentFile(*file_, data::get<music::Metadata>(file_.get()));

  ptr<VirtualFile> newFile(f ? new VirtualFile(*f) : NULL);
  {
    Lock l(instance_->lock_);
    file_.swap(newFile);
  }

  {
    MessageManagerLock l;
    if (file_)
      components()->directoryTree_->refreshNode(*file_);
    if (newFile)
      components()->directoryTree_->refreshNode(*newFile);
    components()->setEnabled(file_);
    components()->waveform_->setLoading(true);
    components()->waveform_->repaint();
  }

  if (false) {
    thread::runInNewThread("CurrentFile loading", 5, this,
                           &CurrentFile::continueLoading, showError);
  } else {
    continueLoading(showError);
  }
}

void CurrentFile::continueLoading(bool showError) {
  length_ = getFileLength(showError);

  if (length_)
    setViewport();

  components()->waveform_->setLoading(false);
  data::setGlobal(file_ ? *file_ : VirtualFile(), CANT_UNDO);
  data::UntypedDataListener::setGlobalDataFile(file_.get());

  if (file_)
    instance_->fillerThread_->startThread();
  menus()->menuItemsChanged();
}

int64 CurrentFile::getFileLength(bool showError) {
  if (!file_ || file::empty(*file_))
    return 0;

  music::MusicFileReader reader(*file_);
  if (!reader.empty()) {
    if (int64 len = bufferFiller()->setReader(*file_, reader.transfer()))
      return len;
    reader.setError(RAN_OUT_OF_MEMORY, RAN_OUT_OF_MEMORY_FULL);
  }

  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  if (showError) {
    juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                      reader.errorTitle(),
                                      reader.errorDetails());
  }

  file_->Clear();
  return 0;
}

void CurrentFile::setViewport() {
  Viewport viewport = data::getProto<Viewport>(file_.get());

  if (!viewport.has_zoom()) {
    Zoom* zoom = viewport.mutable_zoom();
    *zoom = data::getProto<Zoom>(file_.get());  // Legacy files.
    if (!zoom->has_begin())
      zoom->set_begin(0);
    if (!zoom->has_end())
      zoom->set_end(length_);
  }

  if (!viewport.has_loop_points()) {
    LoopPointList* loops = viewport.mutable_loop_points();
    *loops = data::getProto<LoopPointList>(file_.get());  // Legacy files.
    if (!loops->loop_point_size())
      loops->add_loop_point()->set_selected(true);
  }

  viewport.mutable_loop_points()->set_length(length_);
  data::setProto(viewport, file_.get(), CANT_UNDO);
}

void CurrentFile::translateAll() {
  RAN_OUT_OF_MEMORY.translate();
  RAN_OUT_OF_MEMORY_FULL.translate();
}

const VirtualFile CurrentFile::file() const {
  return file_ ? *file_ : VirtualFile();
}

}  // namespace slow
}  // namespace rec
